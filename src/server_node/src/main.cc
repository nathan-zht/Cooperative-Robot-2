#include <signal.h> 
#include <string>
#include "libnavajo/libnavajo.hh"
#include "libnavajo/LogStdOutput.hh"
#include "ros/ros.h"
#include "server_node/status.h"
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
	int pos_x;
	int pos_y;
	int direction;
}Status;

WebServer *webServer = NULL;
char message[255];
Status master,slave;
master_fsm::ServerListener srv_msg;
ros::Subscriber master_status;
ros::Subscriber slave_status;
ros::ServiceClient client;

/* Internal function declaration*/

static void master_status_CB(const server_node::status& status);
static void slave_status_CB(const server_node::status& status);

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
			  if (request->getParameter("command", command) && (command == "rotate" || command == "cross"))
			  {
			      	  ROS_INFO("Formation command received");
			      	  srv_msg.request.command = command;
			      	  srv_msg.request.coordinate_x = 0;
			      	  srv_msg.request.coordinate_y = 0;
			      	  if (client.call(srv_msg)){
			      		ROS_INFO("Sending command to master FSM node");
			      		if(srv_msg.response.status == "SUCCESS"){
							fromString("Formation OK",response);
			      		}else{
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
					  fromString("Go to OK",response);
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
			  fromString("Busy",response);
			  return true;
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


void master_status_CB(const server_node::status& status)
{
	master.state = cobot_state(status.state);
	master.status_str = cobot_state_string[status.state];
	master.pos_x = status.x_pos;
	master.pos_y = status.y_pos;
	ROS_INFO("Master status: %s X_pos=%d y_pos=%d",master.status_str.c_str(),master.pos_x,master.pos_y);
}

void slave_status_CB(const server_node::status& status)
{
	slave.state = cobot_state(status.state);
	slave.status_str = cobot_state_string[status.state];
	slave.pos_x = status.x_pos;
	slave.pos_y = status.y_pos;
	ROS_INFO("Slave status: %s X_pos=%d y_pos=%d",slave.status_str.c_str(),slave.pos_x,slave.pos_y);
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
  LocalRepository myLocalRepo("", "/home/xillinux/cobot/catkin_ws/html");
  webServer->addRepository(&myLocalRepo);

  // Set server port
  webServer->setServerPort(8001);


  // Initialiaze ROS
  ros::init(argc, argv, "server_node");
  ros::NodeHandle n;
  master_status = n.subscribe("master_status", 1000, master_status_CB);
  slave_status = n.subscribe("slave_status", 1000, slave_status_CB);
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


