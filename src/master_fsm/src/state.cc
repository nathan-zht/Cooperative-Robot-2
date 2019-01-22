#include <string>
#include "state.hh"
#include "ros/ros.h"
/* State Definition */
State::State(){
}

State::~State(){
}

void State::executeCommand(){
}

std::string State::getState(){
}

/* Idle state class */
Idle::~Idle(){
}

Idle::Idle(){
	state_id = "IDLE";
}

void Idle::executeCommand(){
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

void ManualControl::setCoordinate(int x, int y){
	x_coordinate = x;
	y_coordinate = y;
}

void ManualControl::executeCommand(){
	ROS_INFO("[Master_FSM] Executing movement to coordinate from manual input...");
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

void CrossFormation::executeCommand(){
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

void OrbitFormation::executeCommand(){
	ROS_INFO("[Master_FSM] Executing Orbit Formation...");
}

std::string OrbitFormation::getState(){
	return state_id;
}
