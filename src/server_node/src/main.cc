#include <signal.h>
#include <string>
#include <sstream>
#include "libnavajo/libnavajo.hh"
#include "libnavajo/LogStdOutput.hh"
#include "ros/ros.h"
#include "master_fsm/status.h"
#include "master_fsm/ServerListener.h"

/* Global variable Declaration */
enum cobot_state{
	IDLE = 0,
	BUSY = 1
};

static const std::string cobot_state_string[] = {
		"Idle",
		"Busy"
};

typedef struct status{
	cobot_state state;
	std::string status_str;
	double pos_x;
	double pos_y;
	double direction;
}Status;

WebServer *webServer = NULL;
char message[255];
Status master,slave;
master_fsm::ServerListener srv_msg;
ros::Subscriber master_status;
ros::Subscriber slave_status;
ros::ServiceClient client;

/* Internal function declaration*/

static void master_status_CB(const master_fsm::status& status);
static void slave_status_CB(const master_fsm::status& status);
static void XML_builder(Status status, std::string &resp_msg);

/* Internal class declaration */
class MyDynamicRepository : public DynamicRepository
{
	private:
		class commandHandler: public DynamicPage
		{
		public:
		  bool getPage(HttpRequest* request, HttpResponse *response)
		  {
			  std::string command, x_pos,y_pos;
			  if (request->getParameter("command", command) && (command == "orbit" || command == "cross"))
			  {
			      	  ROS_INFO("Formation command received");
			      	  srv_msg.request.command = command;
			      	  srv_msg.request.coordinate_x = 0;
			      	  srv_msg.request.coordinate_y = 0;
			      	  ROS_INFO("Sending command to master FSM node");
			      	  if (client.call(srv_msg)){
			      		if(srv_msg.response.status == "SUCCESS"){
					      	ROS_INFO("Response received as SUCCESS");
							fromString("Formation OK",response);
			      		}else{
					      	ROS_INFO("Response received as BUSY");
							fromString("Busy",response);
			      		}
			      	  }else{
				      	ROS_INFO("Failed to send command to master FSM node");
						fromString("ERROR failed to send command to master fsm node",response);
			      	  }
					  return true;
			  }
			  if (request->getParameter("x_pos", x_pos) && request->getParameter("y_pos", y_pos))
			  {
				      ROS_INFO("Go to command received");
			      	  srv_msg.request.command = "manual";
			      	  srv_msg.request.coordinate_x = atof(x_pos.c_str());
			      	  srv_msg.request.coordinate_y = atof(y_pos.c_str());
			      	  ROS_INFO("Sending command to master FSM node");
			      	  if (client.call(srv_msg)){
			      		if(srv_msg.response.status == "SUCCESS"){
					      	ROS_INFO("Response received as SUCCESS");
							fromString("Go to OK",response);
			      		}else{
					      	ROS_INFO("Response received as BUSY");
							fromString("Busy",response);
			      		}
			      	  }else{
				      	ROS_INFO("Failed to send command to master FSM node");
						fromString("ERROR failed to send command to master fsm node",response);
			      	  }
					  return true;
			  }
			  fromString("Unknown Command",response);
			  return false;
		  }
		}commandHandler;

		class statusHandler: public DynamicPage
		{
		private:
			std::string status ;
		public:
		  bool getPage(HttpRequest* request, HttpResponse *response)
		  {
			  std::string command, x_pos,y_pos,resp_msg;
			  if (request->getParameter("cobot", command) && command == "slave")
			  {
			      	  ROS_INFO("Master status request received");
			      	  XML_builder(slave,resp_msg);
					  fromString(resp_msg,response);
					  return true;
			  }
			  if (request->getParameter("cobot", command) && command == "master")
			  {
		      	  	  ROS_INFO("Slave status request received");
			      	  XML_builder(master,resp_msg);
					  fromString(resp_msg,response);
					  return true;
			  }
			  fromString("Unknown Command",response);
			  return false;
		  }
		}statusHandler;
	public:
	MyDynamicRepository() : DynamicRepository()
	{
	  add("command",&commandHandler);
	  add("status",&statusHandler);
	}
};

/* Internal function implementation */
static void exitFunction( int dummy )
{
   if (webServer != NULL) webServer->stopService();
}


void master_status_CB(const master_fsm::status& status)
{
	master.state = cobot_state(status.state);
	master.status_str = cobot_state_string[status.state];
	master.pos_x = status.x_pos;
	master.pos_y = status.y_pos;
	ROS_INFO("Master status: %s X_pos=%f y_pos=%f",master.status_str.c_str(),master.pos_x,master.pos_y);
}

void slave_status_CB(const master_fsm::status& status)
{
	slave.state = cobot_state(status.state);
	slave.status_str = cobot_state_string[status.state];
	slave.pos_x = status.x_pos;
	slave.pos_y = status.y_pos;
	ROS_INFO("Slave status: %s X_pos=%f y_pos=%f",slave.status_str.c_str(),slave.pos_x,slave.pos_y);
}

void XML_builder(Status status, std::string &resp_msg){
	std::stringstream ss;
	resp_msg  = "<COBOT>\n\t<STATUS>";
	resp_msg += status.status_str;
	resp_msg += "</STATUS>\n\t<X_POS>";
	ss << status.pos_x;
	resp_msg += ss.str();
	resp_msg += "</X_POS>\n\t<Y_POS>";
	ss.str(std::string()); // clear the string stream buffer
	ss << status.pos_y;;
	resp_msg += ss.str();
	resp_msg += "</Y_POS>\n</COBOT>";
}

/***********************************************************************/
int main(int argc, char **argv)
{
  // connect signals
  signal( SIGTERM, exitFunction );
  signal( SIGINT, exitFunction );
  
  // Enable logging
  NVJ_LOG->addLogOutput(new LogStdOutput);

  // Load local server repository
  webServer = new WebServer;
  LocalRepository myLocalRepo("", "/home/xillinux/cobot/catkin_ws_fredd/html");
  webServer->addRepository(&myLocalRepo);

  // Set server port
  webServer->setServerPort(8001);


  // Initialiaze ROS
  ros::init(argc, argv, "server_node");
  ros::NodeHandle n;
  master_status = n.subscribe("master_status", 1000, master_status_CB);
  slave_status = n.subscribe("slave_status", 1000, slave_status_CB);
  ROS_INFO("Sending command to master FSM node");
  client = n.serviceClient<master_fsm::ServerListener>("server_listener");

  // Load dynamic server repository
  MyDynamicRepository myRepo;
  webServer->addRepository(&myRepo);
  
  // Create 4 new thread to call ros::spin
  ros::AsyncSpinner spinner(4);
  spinner.start();

  webServer->startService();
  while(ros::ok());
  LogRecorder::freeInstance();
  return 0;
}


