#include <string>
#include "state.hh"
#include "ros/ros.h"
#include "driver_node/driver_srv.h"
/* State Definition */

#define PI 3.14159265


driver_node::driver_srv srv_msg;
static void rotate_left(CobotStatus *master_status, ros::ServiceClient *client){

	/* Roate left 90 */
	int starting_lenc_val = master_status->curr_ticks_left,starting_renc_val = master_status->curr_ticks_right;
	ROS_INFO("[Master_FSM] Rotating left...");
	srv_msg.request.cmd_msg = "rotateleft";
	client->call(srv_msg);
	while(master_status->curr_ticks_left - starting_lenc_val < 10373);
	srv_msg.request.cmd_msg = "stop";
	client->call(srv_msg);
	master_status->direction += 90;
	starting_lenc_val = master_status->curr_ticks_left;
	starting_renc_val = master_status->curr_ticks_right;
}
static void rotate_right(CobotStatus *master_status, ros::ServiceClient *client){

	/* rotate right 90 */
	int starting_lenc_val = master_status->curr_ticks_left,starting_renc_val = master_status->curr_ticks_right;
	ROS_INFO("[Master_FSM] Rotating right...");
	srv_msg.request.cmd_msg = "rotateright";
	client->call(srv_msg);
	while(master_status->curr_ticks_right - starting_renc_val < 12724);
	srv_msg.request.cmd_msg = "stop";
	client->call(srv_msg);
	master_status->direction -= 90;
	starting_lenc_val = master_status->curr_ticks_left;
	starting_renc_val = master_status->curr_ticks_right;

}
static void move_forward();
static void move_backward();

State::State(){
}

State::~State(){
}

void State::executeCommand(CobotStatus *master_status, ros::ServiceClient *client){
}

std::string State::getState(){
}

/* Idle state class */
Idle::~Idle(){
}

Idle::Idle(){
	state_id = "IDLE";
}

void Idle::executeCommand(CobotStatus *master_status, ros::ServiceClient *client){
	ROS_INFO("[Master_FSM] in idle...");
}

std::string Idle::getState(){
	return state_id;
}

/* ManualControl state class */
ManualControl::~ManualControl(){
}

ManualControl::ManualControl(){
	state_id = "MANUAL";
}

void ManualControl::setCoordinate(double x, double y){
	x_coordinate = x;
	y_coordinate = y;
}

void ManualControl::executeCommand(CobotStatus *master_status, ros::ServiceClient *client){
	ROS_INFO("[Master_FSM] Executing movement to coordinate from manual input...");
	ROS_INFO("[Master_FSM] Calculating path...");
	double x_diff = fabs(x_coordinate-master_status->x_pos), y_diff = fabs(y_coordinate-master_status->y_pos);
	unsigned int x_ticks_needed = (unsigned int)(x_diff / cm_per_ticks), y_ticks_needed = (unsigned int)(y_diff / cm_per_ticks);
	int starting_lenc_val = master_status->curr_ticks_left,starting_renc_val = master_status->curr_ticks_right;

	ROS_INFO("[Master_FSM] Orienting X axis...");
	ROS_INFO("[Master_FSM] Curr xpos: %f target x_pos= %f curr_dir %f",master_status->x_pos,x_coordinate,master_status->direction);
	if(x_coordinate < master_status->x_pos){
		switch ((int)(master_status->direction)){
		case 0:
			rotate_left(master_status,client);
			rotate_left(master_status,client);
			break;
		case 90:
			rotate_left(master_status,client);
			break;
		case 270:
			rotate_right(master_status,client);
			break;
		}
	}else if(x_coordinate > master_status->x_pos){
		switch ((int)(master_status->direction)){
			case 180:
				rotate_left(master_status,client);
				rotate_left(master_status,client);
				break;
			case 90:
				rotate_right(master_status,client);
				break;
			case 270:
				rotate_left(master_status,client);
				break;
		}
	}

	ROS_INFO("[Master_FSM] Moving to X target position...");
	srv_msg.request.cmd_msg = "forward";
	client->call(srv_msg);
	ROS_INFO("[Master_FSM] starting %d x_ticks_needed: %d",starting_renc_val,x_ticks_needed);
	while(master_status->curr_ticks_right - starting_renc_val < x_ticks_needed);
	master_status->x_pos = x_coordinate;
	starting_lenc_val = master_status->curr_ticks_left;
	starting_renc_val = master_status->curr_ticks_right;

	ROS_INFO("[Master_FSM] Orienting Y axis...");
	ROS_INFO("[Master_FSM] Curr ypos: %f target y_pos= %f",master_status->y_pos,y_coordinate);
	if(y_coordinate < master_status->y_pos){
		switch ((int)(master_status->direction)){
		case 0:
			rotate_right(master_status,client);
			break;
		case 90:
			rotate_left(master_status,client);
			rotate_left(master_status,client);
			break;
		case 180:
			rotate_left(master_status,client);
			break;
		}
	}else if(y_coordinate > master_status->x_pos){
		switch ((int)(master_status->direction)){
			case 0:
				rotate_left(master_status,client);
				break;
			case 180:
				rotate_right(master_status,client);
				break;
			case 270:
				rotate_left(master_status,client);
				rotate_left(master_status,client);
				break;
		}
	}
	ROS_INFO("[Master_FSM] Moving to Y target position...");
	srv_msg.request.cmd_msg = "forward";
	client->call(srv_msg);
	ROS_INFO("[Master_FSM] starting %d y_ticks_needed: %d",starting_renc_val,y_ticks_needed);
	double update_pos = starting_renc_val;
	while(master_status->curr_ticks_right - starting_renc_val < y_ticks_needed);
	master_status->y_pos = y_coordinate;
	ROS_INFO("[Master_FSM] tick diff %d ",master_status->curr_ticks_right-starting_renc_val);
	starting_lenc_val = master_status->curr_ticks_left;
	starting_renc_val = master_status->curr_ticks_right;
	srv_msg.request.cmd_msg = "stop";
	client->call(srv_msg);

}

std::string ManualControl::getState(){
	return "MANUAL";
}

/* CrossFormation state class */
CrossFormation::~CrossFormation(){
}

CrossFormation::CrossFormation(){
	state_id = "CROSS";
}

void CrossFormation::executeCommand(CobotStatus *master_status, ros::ServiceClient *client){
	ROS_INFO("[Master_FSM] Executing Cross Formation...");
}

std::string CrossFormation::getState(){
	return state_id;
}

/* OrbitFormation state class */
OrbitFormation::~OrbitFormation(){
}

OrbitFormation::OrbitFormation(){
	state_id = "ORBIT";
}

void OrbitFormation::executeCommand(CobotStatus *master_status, ros::ServiceClient *client){
	ROS_INFO("[Master_FSM] Executing Orbit Formation...");
}

std::string OrbitFormation::getState(){
	return state_id;
}
