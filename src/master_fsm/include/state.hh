#ifndef STATE_HH
#define STATE_HH

class State {
  /* class to implement interface.
  only virtual methods should be defined here.
  These can be overriden in individual class definitions. */
  
  public:
  State();
  virtual ~State();
  virtual void executeCommand();
  virtual std::string getState();

  protected:
  std::string state_id;
};

/* State Definition */

class Idle : public State {

	public:
		Idle();
		virtual ~Idle();
		virtual void executeCommand();
		virtual std::string getState();

	protected:
		std::string state_id;
};

class ManualControl : public State{

	  public:
		ManualControl();
		virtual ~ManualControl();
		virtual void setCoordinate(int x, int y);
		virtual void executeCommand();
		std::string getState();

	  protected:
		std::string state_id;
		int x_coordinate;
		int y_coordinate;
};

class CrossFormation : public State {

	public:
		CrossFormation();
		virtual ~CrossFormation();
		virtual void executeCommand();
		virtual std::string getState();

	protected:
		std::string state_id;

};

class OrbitFormation : public State {

	public:
		OrbitFormation();
		virtual ~OrbitFormation();
		virtual void executeCommand();
		virtual std::string getState();

	protected:
		std::string state_id;

};
#endif
