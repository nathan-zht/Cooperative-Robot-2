#ifndef STATE_HH
#define STATE_HH
#include "ros/ros.h"

typedef struct cobot_status{
  int 			state;					// current robot status
  int 			curr_ticks_left;   		// -1 indicate it is not known yet
  int 			curr_ticks_right;		// -1 indicate it is not known yet
  double 		direction;				// robot orientation in degree
  double 		x_pos, y_pos;			// robot coordinate in cm
} CobotStatus;

class State {
  /* class to implement interface.
  only virtual methods should be defined here.
  These can be overriden in individual class definitions. */
  
  public:
  State();
  virtual ~State();
  virtual void executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client);
  virtual std::string getState();

  protected:
  std::string state_id;
};

/* State Definition */

class Idle : public State {

	public:
		Idle();
		virtual ~Idle();
		virtual void executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client);
		virtual std::string getState();

	protected:
		std::string state_id;
};

class ManualControl : public State{

	  public:
		ManualControl();
		virtual ~ManualControl();
		virtual void setCoordinate(double x, double y);
		virtual void executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client);
		std::string getState();

	  protected:
		std::string state_id;
		double x_coordinate;
		double y_coordinate;
};

class CrossFormation : public State {

	public:
		CrossFormation();
		virtual ~CrossFormation();
		virtual void executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client);
		virtual std::string getState();

	protected:
		std::string state_id;

};

class OrbitFormation : public State {

	public:
		OrbitFormation();
		virtual ~OrbitFormation();
		virtual void executeCommand(CobotStatus *slave_status, CobotStatus *master_status, ros::ServiceClient *client, ros::ServiceClient *slave_client);
		virtual std::string getState();

	protected:
		std::string state_id;

};
#endif
