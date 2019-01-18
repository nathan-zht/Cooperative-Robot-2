#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace std;

class State
{
  /*
  purely abstract class to implement interface.
  remember only virtual methods should be defined here.
  These can be overriden in individual class definitions.
  */
  
  public:
  State(){};
  virtual ~State(){};
  
  virtual void doSomething1(){};
  virtual void doSomething2(){}; 

};

class FSM
{
  State idle;
  State manualControl;
  State crossFormation;
  State orbitFormation;
  
  State state = idle;
  
  public:
  FSM(){
    state = idle;
  }
  ~FSM(){}
  
  void setState(State newstate){
    state = newstate;
  }
  
  //getters returning states
  State getIdle(){
    return idle;
  };
  State getManualControl(){
    return manualControl;
  };
};

class Idle : public State
{
  FSM fsm; 
  public:
  Idle(FSM newfsm){
    fsm = newfsm;
  }
  void doSomethingThenMoveState()
  {
    //do something then move state
    fsm.setState(fsm.getManualControl());
  }
};

class ManualControl : public State
{
  FSM fsm; 
  public:
  Idle(FSM newfsm){
    fsm = newfsm;
  }
  void doSomethingThenMoveState()
  {
    //do something then move state
    fsm.setState(fsm.getIdle());
  }
};

int main(int argc, char **argv){

  return 0;
}