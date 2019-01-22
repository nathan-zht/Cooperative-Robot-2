#include <string>
#include "state.hh"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "master_fsm/ServerListener.h"
#include "master_fsm/status.h"
#include "encoder_node/encoder_msg.h"

typedef struct cobot_status{
  std:: string 	state;					// current robot status
  int 			curr_ticks_left;   		// -1 indicate it is not known yet
  int 			curr_ticks_right;		// -1 indicate it is not known yet
  double 		direction;				// robot orientation in degree
  double 		x_pos, y_pos;			// robot coordinate in cm
} CobotStatus;

/* variable initialization */
double cm_per_ticks = 1;
ros::Publisher 		master_status_pub;
ros::Subscriber 	slave_status_sub;
ros::Subscriber 	enc_sub;
master_fsm::status 	master_msg;
CobotStatus 		master_status,slave_status;

/* declare state class instances */
Idle idle;
ManualControl manual;
CrossFormation cross;
OrbitFormation orbit;
State *current_state = &idle;

/* callbacks */

bool fsm(master_fsm::ServerListener::Request &req, master_fsm::ServerListener::Response &res){  
  //state machine here
  std::string coor_x;
  std::string coor_y;
  
  if ((current_state->getState()) == "IDLE"){
    //res.status = "free";
    if(req.command == "manual"){
      current_state = &manual;
      coor_x = req.coordinate_x;
      coor_y = req.coordinate_y;
      ROS_INFO("[Master_FSM] Coordinate x: %d, Coordinate y: %d", req.coordinate_x, req.coordinate_y);
      res.status = "SUCCESS"; //+ req.coordinate_x + req.coordinate_y;
      master_msg.state = 1; //busy
    
    }else if(req.command == "cross"){
      ROS_INFO("[Master_FSM] Cross Desination Coordinates: ");
      current_state = &cross;
      res.status = "SUCCESS";
      master_msg.state = 1;
    
    }else if(req.command == "Orbit"){
      current_state = &orbit;
      ROS_INFO("[Master_FSM] Orbit: ");
      res.status = "SUCCESS";
      master_msg.state = 1;
    }
    
  }else{
    res.status = "NOTSUCCESS";
    master_msg.state = 0;
  }
  
  return true;
};

void slaveStatusCallback(const master_fsm::status& slave_status){
  ROS_INFO("[master_fsm] Slave state: %d", slave_status.state);
}

void encCallback(const encoder_node::encoder_msg enc_msg){
//  if(master_status.curr_ticks_right == -1){
//	  master_status.curr_ticks_right = enc_msg.r_ticks;
//  }
//  if(master_status.curr_ticks_left == -1){
//  	  master_status.curr_ticks_left = enc_msg.r_ticks;
//    }
//  ROS_INFO("[master_fsm] old Direction: %s X %d y %d",master_status.direction.c_str(), master_status.y, master_status.x);
//  if(master_status.direction == "North")
//	  master_status.y += (enc_msg.r_ticks-master_status.curr_ticks_right)*cm_per_ticks;
//  else if(master_status.direction == "South")
//      master_status.y -= (enc_msg.r_ticks-master_status.curr_ticks_right)*cm_per_ticks;
//  else if(master_status.direction == "East")
//      master_status.x += (enc_msg.r_ticks-master_status.curr_ticks_right)*cm_per_ticks;
//  else if(master_status.direction == "South")
//      master_status.x -= (enc_msg.r_ticks-master_status.curr_ticks_right)*cm_per_ticks;
//  master_status.curr_ticks_right = enc_msg.ticks;
//
//  // Publish new status
//  master_msg.x_pos=master_status.x;
//  master_msg.y_pos=master_status.y;
//  master_status_pub.publish(master_msg);
//  ROS_INFO("[master_fsm] New Direction: %s X %d y %d",master_status.direction.c_str(), master_status.y, master_status.x);
}

void init_cobot_status(CobotStatus *cobot){
  cobot->state = "Idle";
  cobot->direction = 90;
  cobot->curr_ticks_right = -1;
  cobot->curr_ticks_left = -1;
  cobot->x_pos = 10;
  cobot->y_pos = 10;
}

int main(int argc, char **argv){

  // Initialize status for master
  init_cobot_status(&master_status);
  init_cobot_status(&slave_status);

  ros::init(argc, argv, "master_fsm");
  ros::NodeHandle n;
  ros::Rate loop_rate(10); //in hz

  //init publishers and subscribers
  master_status_pub = n.advertise<master_fsm::status>("master_status", 1000); 
  slave_status_sub = n.subscribe("slave_status", 1000, slaveStatusCallback);
  enc_sub = n.subscribe("master_enc", 1000, encCallback);
  
  //service server node initialization
  ros::ServiceServer service = n.advertiseService("server_listener", fsm);
  ros::AsyncSpinner spinner(1); // Use 1 thread
  spinner.start();
  
  ROS_INFO("[Master_FSM] Master FSM ready");
  
  while(ros::ok()){
    current_state->executeCommand();
    /*alternative to sleep is the callbacktriggered flag but rosinfo is unreadable
	   if (callbacktriggered == true){
		 callbacktriggered == false;
	   }else{
		 current_state = &idle;
	   }
   */
   current_state = &idle;
   loop_rate.sleep();
  }
/*
  service client node init
  ros::ServiceClient client = n.serviceClient<master_fsm::ServerListener>("server_listener");
  master_fsm::ServerListener srv;
  */
  return 0;
}
