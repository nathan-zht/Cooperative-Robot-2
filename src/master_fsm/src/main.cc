#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace std;

class State
{
  public:
  State(){};
  ~State(){};
  
  virtual void doSomething1(){};
  virtual void doSomething2(){}; 

}

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
  
  State getIdle(){
    return idle;
  };
  State getManualControl(){
    return manualControl;
  };    
  private:
}

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
}

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
}

int main(int argc, char **argv){

  return 0;
}