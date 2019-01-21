#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "master_fsm/ServerListener.h"
#include "master_fsm/status.h"
#include "encoder_node/encoder_msg.h"

typedef struct cobot_status{
  std:: string state, direction;
  int curr_ticks_left;   		// -1 indicate it is not known yet
  int curr_ticks_right;			// -1 indicate it is not known yet
  int x;
  int y;
} CobotStatus;

/* variable initialization */
bool callbacktriggered = false;
int cm_per_ticks = 1;
ros::Publisher master_status_pub; 
ros::Subscriber slave_status_sub;
ros::Subscriber left_enc_sub;
ros::Subscriber right_enc_sub;
master_fsm::status master_msg;
CobotStatus master_status,slave_status;

class State {
  /* class to implement interface.
  only virtual methods should be defined here.
  These can be overriden in individual class definitions. */
  
  public:
  State(){};
  virtual ~State(){}; 
  virtual void executeCommand(){};
  virtual std::string getState(){};

  protected:
  std::string state_id;
};

/* State Definition */

class Idle : public State {
  public:
  Idle(){
    State::state_id = "IDLE";
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
    State::state_id = "MANUAL";
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
};

class CrossFormation : public State {
  public:
  CrossFormation(){
    State::state_id = "CROSS";
  }
  ~CrossFormation(){};
  void executeCommand(){
    ROS_INFO("[Master_FSM] Executing Cross Formation...");
  }
  std::string getState(){ 
    return "CROSS";
  }
};

class OrbitFormation : public State {
  public:
  OrbitFormation(){
    State::state_id = "ORBIT";
  }
  ~OrbitFormation(){};
  void executeCommand(){
    ROS_INFO("[Master_FSM] Executing Orbit Formation...");
  }
  std::string getState(){ 
    return "ORBIT";
  }
};

class Rotate : public State {
  public:
  Rotate(){
    State::state_id = "ROTATE";
  }
  ~Rotate(){};
  void executeCommand(){
    ROS_INFO("[Master_FSM] Executing Rotate...");
  }
  std::string getState(){ 
    return "ROTATE";
  }
};

/* declare state class instances */
Idle idle;
ManualControl manual;
CrossFormation cross;
OrbitFormation orbit;
Rotate rotate;
State *current_state = &idle;

/* callbacks */

bool fsm(master_fsm::ServerListener::Request &req, master_fsm::ServerListener::Response &res){  
  //state machine here
  std::string coor_x;
  std::string coor_y;
  
  if ((current_state->getState()) == "IDLE"){
    //res.status = "free";
    if(req.command == "manual"){
      callbacktriggered = true;
      current_state = &manual;
      coor_x = req.coordinate_x;
      coor_y = req.coordinate_y;
      //current_state->executeCommand();
      ROS_INFO("[Master_FSM] Coordinate x: %d, Coordinate y: %d", req.coordinate_x, req.coordinate_y);
      res.status = "SUCCESS"; //+ req.coordinate_x + req.coordinate_y;
      master_msg.state = 1; //busy
    
    }else if(req.command == "cross"){
      ROS_INFO("[Master_FSM] Cross Desination Coordinates: ");      
      res.status = "SUCCESS";
      master_msg.state = 1;
    
    }else if(req.command == "rotate"){
      ROS_INFO("[Master_FSM] Rotate: ");      
      res.status = "SUCCESS";
      master_msg.state = 1;
    }
    
  }else{
    res.status = "NOTSUCCESS";
    master_msg.state = 0;
  }
  
  return true;
};

void slaveStatusCallback(const master_fsm::status& slave_status){
  ROS_INFO("[master_fsm] Slave state: %d", slave_status.state);
}

void rightEncCallback(const encoder_node::encoder_msg right_enc){
  if(master_status.curr_ticks_right == -1){
	  master_status.curr_ticks_right = right_enc.ticks;
  }
  ROS_INFO("[master_fsm] old Direction: %s X %d y %d",master_status.direction.c_str(), master_status.y, master_status.x);
  if(master_status.direction == "North")
	  master_status.y += (right_enc.ticks-master_status.curr_ticks_right)*cm_per_ticks;
  else if(master_status.direction == "South")
      master_status.y -= (right_enc.ticks-master_status.curr_ticks_right)*cm_per_ticks;
  else if(master_status.direction == "East")
      master_status.x += (right_enc.ticks-master_status.curr_ticks_right)*cm_per_ticks;
  else if(master_status.direction == "South")
      master_status.x -= (right_enc.ticks-master_status.curr_ticks_right)*cm_per_ticks;
  master_status.curr_ticks_right = right_enc.ticks;

  // Publish new status
  master_msg.x_pos=master_status.x;
  master_msg.y_pos=master_status.y;
  master_status_pub.publish(master_msg);
  ROS_INFO("[master_fsm] New Direction: %s X %d y %d",master_status.direction.c_str(), master_status.y, master_status.x);
}

void leftEncCallback(const encoder_node::encoder_msg left_enc){
  ROS_INFO("[master_fsm] Left encoder data | ticks: %d direction %d", left_enc.ticks, left_enc.direction);
}

int main(int argc, char **argv){

  // Initialize status for master
  master_status.state = "Idle";
  master_status.direction = "North";
  master_status.curr_ticks_right = -1;
  master_status.curr_ticks_left = -1;
  master_status.x = 10;
  master_status.y = 10;

  slave_status.state = "Idle";
  slave_status.direction = "North";
  slave_status.curr_ticks_right = -1;
  slave_status.curr_ticks_left = -1;
  slave_status.x = 0;
  slave_status.y = 0;

  ros::init(argc, argv, "master_fsm");
  ros::NodeHandle n;
  ros::Rate loop_rate(10); //in hz

  //init publishers and subscribers
  master_status_pub = n.advertise<master_fsm::status>("master_status", 1000); 
  slave_status_sub = n.subscribe("slave_status", 1000, slaveStatusCallback);
  right_enc_sub = n.subscribe("right_enc", 1000, rightEncCallback);
  left_enc_sub = n.subscribe("left_enc", 1000, leftEncCallback);
  
  //service server node initialization
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
