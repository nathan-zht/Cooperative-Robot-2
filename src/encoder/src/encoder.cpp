#include "ros/ros.h"
#include "std_msgs/String.h"
#include "encoder/EncoderInfo.h"

#include <sstream>
#include <fstream>

int main(int argc, char **argv){
  ros::init(argc, argv, "encoder_node");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<encoder::EncoderInfo>("encoderInfo", 1000);
  ros::Rate loop_rate(10);

  int8_t direction0;
  int8_t direction1;
  int8_t distance0;
  int8_t distance1;
  int8_t ticks0;
  int8_t ticks1;
  int encoder0_data;
  int encoder1_data;
  
  encoder::EncoderInfo msg;

  std::ifstream Encoder0;
  std::ifstream Encoder1;

  while(ros::ok()){
    Encoder0.open("/dev/ENC0");
    Encoder1.open("/dev/ENC1/");
    
    Encoder0 >> encoder0_data;
    Encoder1 >> encoder1_data;
    
    direction0 = (encoder0_data & 0x80000000)>>31;
    ticks0 = encoder0_data & 0x7FFFFFFF;
    direction1 = (encoder1_data & 0x80000000)>>31;
    ticks1 = encoder0_data & 0x7FFFFFFF;
    
    std::cout <<std::endl << "Encoder 0: " << "position: " << ticks0 << " | Direction: " << direction0;
    std::cout <<std::endl << "Encoder 1: " << "position: " << ticks1 << " | Direction: " << direction1;
    
    //publish
    msg.direction0 = direction0;
    msg.direction1 = direction1;
    //msg.ticks0 = ticks0;
    //msg.ticks1 = ticks1;
    
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}
