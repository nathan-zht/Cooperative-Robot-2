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
std::string val;
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
    ROS_INFO("[Master_FSM] Executing movement to coordinate from manual input...");
    //testing
    //std::cout << std::endl << "Manual Control Command Execute Going to coordinates x: " << x_coordinate << " y: " << y_coordinate << std::endl;
    //if the following are uncommented, the process will  halt until there is input from user.
    //std::cout << "Enter a new value: " << std::endl;
    //std::cin >> val;
  }
  
  std::string getState(){
    return "MANUAL";
  }
  void setState(){}
};

Idle idle;
ManualControl manual;
State *current_state = &idle;

bool callbacktriggered = false;

bool fsm(master_fsm::ServerListener::Request &req, 
  master_fsm::ServerListener::Response &res){
  //state machine here
  std::string coor_x;
  std::string coor_y;
  if ((current_state->getState()) == "IDLE"){
    //res.status = "free";
    if(req.command == "manual"){
      callbacktriggered = true;
      current_state = &manual;
      current_state->setCoordinate(req.coordinate_x, req.coordinate_y);
      coor_x = req.coordinate_x;
      coor_y = req.coordinate_y;
      //current_state->executeCommand();
      ROS_INFO("[Master_FSM] Coordinate x: %d, Coordinate y: %d", req.coordinate_x, req.coordinate_y);
      res.status = "SUCCESS"; //+ req.coordinate_x + req.coordinate_y;
    }
  }else{
    res.status = "NOTSUCCESS";
  }
  return true;
};

int main(int argc, char **argv){
  //initialization
  ros::init(argc, argv, "master_fsm");
  ros::NodeHandle n;
  
  ros::Rate loop_rate(10); //in hz
  //ros::Duration().sleep may also be an option
  
  //service server node init
  ros::ServiceServer service = n.advertiseService("server_listener", fsm);
  ros::AsyncSpinner spinner(1); // Use 1 thread
  spinner.start();
  ROS_INFO("[Master_FSM] Master FSM ready");
  while(ros::ok()){
    current_state->executeCommand();
    /*current_state->executeCommand();
    may need to be executed more than once or
    it may not be execute outside of idle*/
   /*alternative to sleep is the callbacktriggered flag but rosinfo is unreadable
   if (callbacktriggered == true){
     callbacktriggered == false;
   }else{
     current_state = &idle;
   }
   */
   current_state = &idle;
   loop_rate.sleep();
  }
/*
  service client node init
  ros::ServiceClient client = n.serviceClient<master_fsm::ServerListener>("server_listener");
  master_fsm::ServerListener srv;
  */
  return 0;
}
