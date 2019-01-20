#include <iostream>
#include <fstream>

#include "ros/ros.h"
#include "driver_node/driver_srv.h"
#include "pwm.hh"

bool serviceCallback(driver_node::driver_srv::Request  &req,
         driver_node::driver_srv::Response &res)
{
  ROS_INFO("request: %s", req.cmd_msg.c_str());
  ROS_INFO("sending back response: [%s]", "OK");
  res.resp_msg = "OK";
  return true;
}

int main(int argc, char **argv){
  int input;
  ros::init(argc,argv,"driver_node");
  pwm_set_enable("PWM0");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("master_driver", serviceCallback);
  ros::spin();
  return 0;
}
