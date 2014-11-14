#include "WaitProcess.h"


// in milliseconds
WaitProcess::WaitProcess(int callbkCoroutine, float waitSeconds) : 
	LuaCallbackProcess(callbkCoroutine)
{
	elapsedTime = 0.0f;
	waitInSeconds = waitSeconds;
	//cout << "!!elapsed time: " << elapsedTime << endl;
	//cout << "!!target time: " << waitInSeconds << "." << endl;
}

// in seconds
WaitProcess::WaitProcess(int callbkCoroutine, int waitInMilliseconds) :
	LuaCallbackProcess(callbkCoroutine)
{
	elapsedTime = 0.0f;
	waitInSeconds = waitInMilliseconds / 1000.0f;
	//cout << "!!elapsed time: " << elapsedTime << endl;
	//cout << "!!target time: " << waitInSeconds << "." << endl;
}

WaitProcess::~WaitProcess()
{


}


// dt in milliseconds
void WaitProcess::update(float dt)
{
	elapsedTime += dt;
	if (elapsedTime > waitInSeconds)
	{
		deactivate();
	}
}

void WaitProcess::start()
{


}

void WaitProcess::onFinish()
{
	LuaCallbackProcess::onFinish();
}