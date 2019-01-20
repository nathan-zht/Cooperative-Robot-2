#include <iostream>
#include <fstream>
#include <string>
#include "ros/ros.h"
#include "driver_node/driver_srv.h"
#include "pwm.hh"

static void driver_node_info(const std::string str){
	ROS_INFO("[Master Driver] %s",str.c_str());
}

static SYSFS_RES forward(){
	driver_node_info("Moving forward");
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	return SUCCESS;
}

static SYSFS_RES backward(){
	driver_node_info("Moving backward");
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	return SUCCESS;
}

static SYSFS_RES rotate_left(){
	driver_node_info("Rotating to left");
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	return SUCCESS;
}

static SYSFS_RES rotate_right(){
	driver_node_info("Rotating to right");
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	return SUCCESS;
}

static SYSFS_RES stop(){
	driver_node_info("Stopping robot");
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	if(pwm_set_duty("PWM0",10000) == FAILED){
		driver_node_info("Failed to set PWM0 dutycycle");
		return FAILED;
	}
	return SUCCESS;
}


bool serviceCallback(driver_node::driver_srv::Request  &req,
         driver_node::driver_srv::Response &res)
{
	std::string cmd = req.cmd_msg;

	if(cmd.compare("forward") == 0){
		if(forward() == FAILED){
			res.resp_msg = "FAIL";
			return 1;
		}else{
			res.resp_msg = "SUCCESS";
			return 1;
		}
	}else if(cmd.compare("backward") == 0){
		if(backward() == FAILED){
			res.resp_msg = "FAIL";
			return 1;
		}else{
			res.resp_msg = "SUCCESS";
			return 1;
		}
	}else if(cmd.compare("rotateleft") == 0){
		if(rotate_left() == FAILED){
			res.resp_msg = "FAIL";
			return 1;
		}else{
			res.resp_msg = "SUCCESS";
			return 1;
		}
	}else if(cmd.compare("rorateright") == 0){
		if(rotate_right() == FAILED){
			res.resp_msg = "FAIL";
			return 1;
		}else{
			res.resp_msg = "SUCCESS";
			return 1;
		}
	}else if(cmd.compare("stop") == 0){
		if(stop() == FAILED){
			res.resp_msg = "FAIL";
			return 1;
		}else{
			res.resp_msg = "SUCCESS";
			return 1;
		}
	//}
	//else if(cmd.compare("setspeed") == 0){
	//	setspeed();
	}else{
		res.resp_msg = "UNKNOWN_CMD";
		return 1;
	}



//
//  ROS_INFO("request: %s", req.cmd_msg.c_str());
//  ROS_INFO("sending back response: [%s]", "OK");
//  res.resp_msg = "OK";
  return true;
}

int main(int argc, char **argv){
	driver_node_info("Starting node");

	/* Initialize the PWM register */
	driver_node_info("Initializing PWMs");
	if(pwm_set_enable("PWM0") == FAILED){
	  driver_node_info("Failed to enable PMW0");
	  return 0;
	}

	if(pwm_set_enable("PWM1") == FAILED){
	  driver_node_info("Failed to enable PWM1");
	  return 0;
	}
	stop();

	/* Initialize ROS */
	driver_node_info("Initializing ROS");
	ros::init(argc,argv,"driver_node");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("master_driver", serviceCallback);
	ros::spin();
	return 0;
}
