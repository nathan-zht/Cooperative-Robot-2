#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "ros/ros.h"
#include "encoder_node/encoder_msg.h"

std::ifstream sysfs;

bool timer_trip=0;;

bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

int enc_read(const std::string ENC, encoder_node::encoder_msg enc_msg){
	std::string path = "/dev/" + ENC;
	if(fileExists(path)){
		sysfs.open(path.c_str());
	}
	else{
		ROS_ERROR("%s didn't exist",path.c_str());
		return -1;
	}
	int data = sysfs.get();
	enc_msg.direction = (data % 0x80000000) >> 31;
	enc_msg.ticks = data % 0x7fffffff;
	return 0;
}

void timerCallback(const ros::TimerEvent&){
	timer_trip = true;
}

int main(int argc, char **argv){

	/* ROS initialization */
	ros::init(argc, argv, "encoder_node");
	ros::NodeHandle n;
	ros::Timer timer = n.createTimer(ros::Duration(0.01), timerCallback);
	ros::Publisher left_enc = n.advertise<encoder_node::encoder_msg>("left_enc",1000);
	ros::Publisher right_enc = n.advertise<encoder_node::encoder_msg>("right_enc",1000);
	timer.start();

	/* Declare each encoder message */
	encoder_node::encoder_msg ENC0_msg,ENC1_msg;
	ROS_INFO("[Encoder Node] Starting...");
	while(ros::ok()){
		ros::spinOnce();
		if(timer_trip){

			ROS_INFO("[Encoder Node] Publishing left_enc...");
			if(enc_read("ENC0",ENC0_msg) == 0)
				left_enc.publish(ENC0_msg);
			else
				ROS_ERROR("[Encoder Node] Failed to read ENC0.");

			ROS_INFO("[Encoder Node] Publishing right_enc...");
			if(enc_read("ENC1",ENC1_msg) == 0)
				right_enc.publish(ENC1_msg);
			else
				ROS_ERROR("[Encoder Node] Failed to read ENC0.");

			timer_trip = false;
		}
	}
	return 0;
}
