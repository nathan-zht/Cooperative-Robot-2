#include <string>
#include <cmath>
#include "state.hh"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "master_fsm/ServerListener.h"
#include "master_fsm/status.h"
#include "driver_node/driver_srv.h"
#include "encoder_node/encoder_msg.h"

/* variable initialization */
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
  
  if ((current_state->getState()) == "IDLE"){
    //res.status = "free";
    if(req.command == "manual"){
      current_state = &manual;
      manual.setCoordinate(req.coordinate_x,req.coordinate_y);
      ROS_INFO("[Master_FSM] Coordinate x: %d, Coordinate y: %d", req.coordinate_x, req.coordinate_y);
      res.status = "SUCCESS"; //+ req.coordinate_x + req.coordinate_y;
      master_msg.state = 1; //busy
    
    }else if(req.command == "cross"){
      ROS_INFO("[Master_FSM] Cross Desination Coordinates: ");
      current_state = &cross;
      res.status = "SUCCESS";
      master_msg.state = 1;
    
    }else if(req.command == "orbit"){
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
  master_status.curr_ticks_right = enc_msg.r_ticks;
  master_status.curr_ticks_left = enc_msg.l_ticks;

//  master_status.y_pos += (enc_msg.r_ticks-master_status.curr_ticks_right)*cm_per_ticks*sin(master_status.direction);
//  master_status.x_pos += (enc_msg.r_ticks-master_status.curr_ticks_right)*cm_per_ticks*cos(master_status.direction);
//  master_status.curr_ticks_right = enc_msg.r_ticks;

  //ROS_INFO("[master_fsm] New Direction: %f X %f y %f",master_status.direction, master_status.y_pos, master_status.x_pos);
}

void init_cobot_status(CobotStatus *cobot){
  cobot->state = "Idle";
  cobot->direction = 90;
  cobot->curr_ticks_right = -1;
  cobot->curr_ticks_left = -1;
  cobot->x_pos = 10;
  cobot->y_pos = 10;
}

void timerCallback(const ros::TimerEvent& e){
	master_msg.x_pos = master_status.x_pos;
	master_msg.y_pos = master_status.y_pos;
	master_status_pub.publish(master_msg);
}

int main(int argc, char **argv){

  /* Initialize status for master */
  init_cobot_status(&master_status);
  init_cobot_status(&slave_status);

  ros::init(argc, argv, "master_fsm");
  ros::NodeHandle n;
  ros::Rate loop_rate(10); //in hz

  /* init publishers and subscribers */
  master_status_pub = n.advertise<master_fsm::status>("master_status", 1000); 
  slave_status_sub = n.subscribe("slave_status", 1000, slaveStatusCallback);
  enc_sub = n.subscribe("master_enc", 1000, encCallback);
  ros::Timer timer = n.createTimer(ros::Duration(0.1), timerCallback);

  /* service server node initialization */
  ros::ServiceServer service = n.advertiseService("server_listener", fsm);
  ros::AsyncSpinner spinner(1); // Use 1 thread
  spinner.start();
  

  /* service client node init */
  ros::ServiceClient client = n.serviceClient<driver_node::driver_srv>("master_driver");

  ROS_INFO("[Master_FSM] Master FSM ready");
  while(ros::ok()){
    current_state->executeCommand(&master_status, &client);
    /*alternative to sleep is the callbacktriggered flag but rosinfo is unreadable
	   if (callbacktriggered == true){
		 callbacktriggered == false;
	   }else{
		 current_state = &idle;
	   }
   */
   current_state = &idle;
   master_msg.state = 0;
   loop_rate.sleep();
  }
/*
  service client node init
  ros::ServiceClient client = n.serviceClient<master_fsm::ServerListener>("server_listener");
  master_fsm::ServerListener srv;
  */
  return 0;
}
