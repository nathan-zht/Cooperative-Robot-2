#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "master_fsm/ServerListener.h"
/*
using namespace std;
typedef enum State{
  IDLE,
  MANUALCONTROL
}State;

    State curr_state = IDLE;
*/

class State {
  /*
  class to implement interface.
  remember only virtual methods should be defined here.
  These can be overriden in individual class definitions.
  */
  public:
  State(){};
  virtual ~State(){}; 
  virtual void executeCommand(){};
  virtual std::string getState(){};
  virtual void setCoordinate(int x, int y){};
  protected:
  std::string id;
};

class Idle : public State {
  public:
  Idle(){
    State::id = "IDLE";
  }
  void executeCommand(){
    //do something then move state
    ROS_INFO("[Master_FSM] in idle...");
  }
  std::string getState(){
    return "IDLE";
  }
};

class ManualControl : public State{
  public:
  int x_coordinate;
  int y_coordinate;
  ManualControl(){
    State::id = "MANUAL";
  }
  void setCoordinate(int x, int y){
    x_coordinate = x;
    y_coordinate = y;
  }
  
  void executeCommand(){
    std::cout << std::endl <<"Going to coordinates x: " << x_coordinate << " y: " << y_coordinate << std::endl;
  }
  
  std::string getState(){
    return "MANUAL";
  }
  void setState(){}
};

Idle idle;
ManualControl manual;
State current_state = idle;

bool fsm(master_fsm::ServerListener::Request &req, 
  master_fsm::ServerListener::Response &res){
  //state machine here
  //return true when service is complete
  //res.status;
  
  if (current_state.getState() == "IDLE"){
    res.status = "free";
    if(req.command == "manual"){
      current_state = manual;
      current_state.setCoordinate(req.coordinate_x, req.coordinate_y);
      res.status = "busy";
    }
  } 
};

int main(int argc, char **argv){
  //initialization
  ros::init(argc, argv, "master_fsm");
  ros::NodeHandle n;
  //service server node init
  ros::ServiceServer service = n.advertiseService("server_listener", fsm);
  ros::AsyncSpinner spinner(1); // Use 1 thread
  spinner.start();
  ROS_INFO("[Master_FSM] Master FSM ready");
  while(ros::ok()){
    current_state.executeCommand();
    current_state = idle;
  }
  
/*
  service client node init
  ros::ServiceClient client = n.serviceClient<master_fsm::ServerListener>("server_listener");
  master_fsm::ServerListener srv;
  */
  return 0;
}
