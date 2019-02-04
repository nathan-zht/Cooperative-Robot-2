#include <string>
#include "state.hh"
#include "ros/ros.h"
#include "driver_node/driver_srv.h"
#include "slave_fsm/ServerListener.h"
/* State Definition */

#define PI 3.14159265
#define cm_per_ticks  0.003225
#define wheel_base 38.8//44.45

driver_node::driver_srv srv_msg;
slave_fsm::ServerListener slave_cmd;

static void rotate_left(CobotStatus *master_status, ros::ServiceClient *driver, double target_dir, double curr_dir){

	/* Rotate left */
	int ticks_needed = (int)(fabs((target_dir-curr_dir)*PI/180)*wheel_base/(cm_per_ticks)*1.1);
	int starting_lenc_val = master_status->curr_ticks_left,
		starting_renc_val = master_status->curr_ticks_right;
	ROS_INFO("[Master_FSM] Calculated direction: %f direction_ticks: %d", target_dir - curr_dir,ticks_needed);
	ROS_INFO("[Master_FSM] Rotating left");
	srv_msg.request.cmd_msg = "rotateleft";
	driver->call(srv_msg);
	while(abs(master_status->curr_ticks_left - starting_lenc_val) + abs(master_status->curr_ticks_right - starting_renc_val) < ticks_needed);
	srv_msg.request.cmd_msg = "stop";
	driver->call(srv_msg);
	master_status->direction = target_dir;
	ROS_INFO("[Master_FSM] Curr direction_ticks: %f",  target_dir);
}
static void rotate_right(CobotStatus *master_status, ros::ServiceClient *driver, double target_dir, double curr_dir){

	/* Rotate right */
	int ticks_needed = (int)(fabs((curr_dir-target_dir)*PI/180)*wheel_base/(cm_per_ticks)*1.1);
	int starting_lenc_val = master_status->curr_ticks_left,
		starting_renc_val = master_status->curr_ticks_right;

	ROS_INFO("[Master_FSM] Calculated direction: %f direction_ticks: %d", curr_dir - target_dir,ticks_needed);
	ROS_INFO("[Master_FSM] Rotating right");
	srv_msg.request.cmd_msg = "rotateright";
	driver->call(srv_msg);
	while(abs(master_status->curr_ticks_left - starting_lenc_val) + abs(master_status->curr_ticks_right - starting_renc_val) < ticks_needed);
	srv_msg.request.cmd_msg = "stop";
	driver->call(srv_msg);
	master_status->direction = target_dir;
	ROS_INFO("[Master_FSM] Curr direction_ticks: %f",  target_dir);
}

static void move_to_xy(CobotStatus *master_status, ros::ServiceClient *driver, double x_target, double y_target){
	ROS_INFO("[Master_FSM] Calculating path...");
	double x_diff = x_target-master_status->x_pos, y_diff = y_target-master_status->y_pos;

	/* Calculate distance between curr_pos and target_pos */
	double distance = sqrt( pow( x_diff, 2) + pow( y_diff, 2));
	int distance_ticks = (int)(distance / cm_per_ticks);

	/* Calculate target direction */
	double target_dir;
	if(x_diff == 0){
		if(y_diff > 0)
			target_dir = 90;
		else if(y_diff < 0)
			target_dir = 270;
		else
			target_dir = master_status->direction;
	}else if (x_diff > 0){
		if(atan(y_diff/x_diff) < 0 ){
			target_dir = 360 + atan(y_diff/x_diff)/PI*180;
		}else
			target_dir = atan(y_diff/x_diff)/PI*180;
	}else{
			target_dir = 180 + atan(y_diff/x_diff)/PI*180;
	}

	/* Turn to smaller direction degree difference */
	if (target_dir - master_status->direction < 360 - (target_dir - master_status->direction)){
		rotate_right(master_status , driver, target_dir, master_status->direction);
	}else {
		rotate_left(master_status, driver, target_dir,master_status->direction);
	}

	/* Move toward target pos */
	ROS_INFO("[Master_FSM] Calculated distance: %f distance_ticks %d", distance, distance_ticks);
	int starting_lenc_val = master_status->curr_ticks_left,
		starting_renc_val = master_status->curr_ticks_right;
	srv_msg.request.cmd_msg = "forward";
	driver->call(srv_msg);
	while((master_status->curr_ticks_left - starting_lenc_val) + (master_status->curr_ticks_right - starting_renc_val) < distance_ticks);
	srv_msg.request.cmd_msg = "stop";
	driver->call(srv_msg);
	master_status->x_pos = x_target;
	master_status->y_pos = y_target;
}

static void move_forward();
static void move_backward();

State::State(){
}

State::~State(){
}

void State::executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client){
}

std::string State::getState(){
}

/* Idle state class */
Idle::~Idle(){
}

Idle::Idle(){
	state_id = "IDLE";
}

void Idle::executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client){
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

void ManualControl::executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client){
	ROS_INFO("[Master_FSM] Executing movement to coordinate from manual input...");
	move_to_xy(master_status, client, x_coordinate, y_coordinate);

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

void CrossFormation::executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client){
	ROS_INFO("[Master_FSM] Executing Cross Formation...");
	double starting_x = master_status->x_pos, starting_y = master_status->y_pos;

	/* Move slave to X+100 and Y-50 */
	slave_cmd.request.command = "manual";
	slave_cmd.request.coordinate_x = starting_x+75;
	slave_cmd.request.coordinate_y = starting_y-125;
	if(slave_client->call(slave_cmd)){
		ROS_INFO("[Master_FSM] Command sent to slave response:%s ",slave_cmd.response.status.c_str());
		/* wait status change */
		while(slave_status->state == 0);
	}else{
		ROS_INFO("[Master_FSM] Command failed to send");
		return;
	}

	/* Wait slave is done moving */
	while(slave_status->state == 1);

	/* Move master to X and Y-100 */
	move_to_xy(master_status, client, starting_x, starting_y-400);

	/* Move slave to X-100 and Y-50 */
	slave_cmd.request.command = "manual";
	slave_cmd.request.coordinate_x = starting_x-150;
	slave_cmd.request.coordinate_y = starting_y-125;
	if(slave_client->call(slave_cmd)){
		ROS_INFO("[Master_FSM] Command sent to slave response:%s ",slave_cmd.response.status.c_str());
		/* wait status change */
		while(slave_status->state == 0);
	}else{
		ROS_INFO("[Master_FSM] Command failed to send");
		return;
	}
	/* Wait slave is done moving */
	while(slave_status->state == 1);

	/* Move master to original position*/
	move_to_xy(master_status, client, starting_x, starting_y);

	/* Move slave to X+100 and Y-50 */
	slave_cmd.request.command = "manual";
	slave_cmd.request.coordinate_x = starting_x+75;
	slave_cmd.request.coordinate_y = starting_y-125;
	if(slave_client->call(slave_cmd)){
		ROS_INFO("[Master_FSM] Command sent to slave response:%s ",slave_cmd.response.status.c_str());
		/* wait status change */
		while(slave_status->state == 0);
	}else{
		ROS_INFO("[Master_FSM] Command failed to send");
		return;
	}
	/* Wait slave is done moving */
	while(slave_status->state == 1);



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

void OrbitFormation::executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client){
	ROS_INFO("[Master_FSM] Executing Orbit Formation...");

}

std::string OrbitFormation::getState(){
	return state_id;
}
