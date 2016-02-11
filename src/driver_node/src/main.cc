#include <iostream>
#include <fstream>

#include "ros/ros.h"
#include "driver_node/driver_setting.h"

std::ofstream sysfs;

void pwm_set_duty(int dutycycle){
  sysfs.open("/sys/class/PWM/PWM0/DUTY");
  sysfs << dutycycle;
  sysfs.close();
}
void pwm_set_period(int period){
  sysfs.open("/sys/class/PWM/PWM0/PERIOD");
  sysfs << period;
  sysfs.close();
}

void pwm_set_enable(int enable){
  sysfs.open("/sys/class/PWM/PWM0/ENABLE");
  sysfs << enable;
  sysfs.close();
}
void subCallback(const driver_node::driver_setting::ConstPtr& msg){
	ROS_INFO("Setting PWM driver to Period: [%d] Duty: [%d] Wheel: [%d]", msg->period,msg->duty,msg->wheel);
	//pwm_set_period(msg->period);
	if(msg->wheel == 1 )
		ROS_INFO("Right duty in periods: %d",(int((double)msg->period*((double)msg->duty/100))));
	else
		ROS_INFO("Left duty in periods: %d",(int((double)msg->period*((double)msg->duty/100))));
		
	//pwm_set_duty(msg->period*(msg->duty/100));
}
int main(int argc, char **argv){
  int input;
  ros::init(argc,argv,"driver_node");
  pwm_set_enable(3);
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("driver_setting",10,subCallback);
  ros::spin();
  return 0;
}
