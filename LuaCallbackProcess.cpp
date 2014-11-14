#include "LuaCallbackProcess.h"

LuaCallbackProcess::LuaCallbackProcess(int callbkCoroutineIndex)
	: Process()
	, coroutineIndex(callbkCoroutineIndex)
{
	
}

LuaCallbackProcess::LuaCallbackProcess()
	: Process()
{

	coroutineIndex = -1;
}

LuaCallbackProcess::~LuaCallbackProcess()
{

}

void LuaCallbackProcess::onFinish()
{
	// callback with the coroutineIndex
	// unless it's -1, which means the process
	// did not register any callback
	if (coroutineIndex != -1)
		Services::luaInterface()->resumeCoroutine(coroutineIndex);

}