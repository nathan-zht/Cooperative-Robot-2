#include <stdio.h>
#include <string>
#include <sstream>
#include <sys/stat.h>
#include "ros/ros.h"
#include "encoder_node/encoder_msg.h"

FILE* sysfs;

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

int enc_read(const std::string ENC, encoder_node::encoder_msg *enc_msg){
	std::string path = "/dev/" + ENC;
	sysfs = fopen(path.c_str(),"r");
	if(sysfs == NULL){
		ROS_ERROR("%s didn't exist",path.c_str());
		return -1;
	}
	long int data;
	fscanf(sysfs,"%ld",&data);
	fclose(sysfs);
	if(ENC == "ENC0"){
		/* Make sure that both encoder shows 1 for direction when moving forward
		 * and ticks increase when moving forward and decrease when moving backward
		 */
		enc_msg->r_direction = 1 -((data & 0x80000000) >> 31);
		enc_msg->r_ticks = 0x7fffffff - (data & 0x7fffffff);
	}
	else{
		enc_msg->l_direction = (data & 0x80000000) >> 31;
		enc_msg->l_ticks =  (data & 0x7fffffff);
	}
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
	ros::Publisher enc_pub = n.advertise<encoder_node::encoder_msg>("master_enc",1000);
	timer.start();

	/* Declare encoder message */
	encoder_node::encoder_msg ENC_msg;
	ROS_INFO("[Encoder Node] Starting...");
	while(ros::ok()){
		ros::spinOnce();
		if(timer_trip){

			ROS_INFO("[Encoder Node] Reading encoders...");
			if(enc_read("ENC0",&ENC_msg) != 0)
				ROS_ERROR("[Encoder Node] Failed to read ENC0.");

			if(enc_read("ENC1",&ENC_msg) == 0)
				enc_pub.publish(ENC_msg);
			else
				ROS_ERROR("[Encoder Node] Failed to read ENC1.");

			timer_trip = false;
		}
	}
	return 0;
}
