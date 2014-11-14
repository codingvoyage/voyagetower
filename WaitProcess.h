#ifndef WAITPROCESS_H
#define WAITPROCESS_H

class LuaCallbackProcess;
#include "LuaCallbackProcess.h"
#include <lua.hpp>
#include <iostream>
using namespace std;

class WaitProcess : public LuaCallbackProcess
{
private:
public:

	float					waitInSeconds;
	float					elapsedTime;

	WaitProcess				(int callbkCoroutine, float waitSeconds);
	WaitProcess				(int callbkCoroutine, int waitInMilliseconds);
	~WaitProcess();

	void update				(float dt);
	void start();
	void onFinish();

};



#endif
