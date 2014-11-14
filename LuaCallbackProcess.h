#ifndef LUACALLBACKPROCESS_H
#define LUACALLBACKPROCESS_H

#include "Services.h"
#include "Process.h"
#include <lua.hpp>

class LuaCallbackProcess : public Process
{
protected:
	int coroutineIndex;

public:

	LuaCallbackProcess(int callbkCoroutineIndex);
	LuaCallbackProcess();
	~LuaCallbackProcess();

	void onFinish();

};


#endif
