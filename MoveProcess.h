#ifndef MOVEPROCESS_H
#define MOVEPROCESS_H

class LuaCallbackProcess;
#include <cmath>
#include "LuaCallbackProcess.h"

class MoveProcess : public LuaCallbackProcess
{
private:
	int				targetObjectID;
	float			distanceElapsed;
	float			targetDistance;
	float			vx;
	float			vy;
public:
	~MoveProcess(); //Destructor
	MoveProcess(int callbkCoroutine, int targetObjectID, float targetDistance,
		float vx, float vy);
	MoveProcess(int targetObjectID, float targetDistance,
		float vx, float vy);

	void update(float dt);
	void start();
	void onFinish();
};

#endif