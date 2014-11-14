#ifndef PROCESS_H
#define PROCESS_H

class Process
{
private:
	bool active;
	// field for objects used

protected:
	// Only children of the class can set active to false
	void deactivate();

	// method to register objects used.


public:
	Process();
	~Process();
	virtual void update(float dt) {}
	virtual void start() {}
	virtual void onFinish() {}
	bool isActive();
};



#endif