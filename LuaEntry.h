// A dummy process meant to immediately call a 
// coroutine for the first time
#ifndef LUAENTRY_H
#define LUAENTRY_H

#include "LuaCallbackProcess.h"
#include "LuaInterface.h"

class LuaEntry : public LuaCallbackProcess
{
private:
	LuaInterface::LuaValue* callValues;
	int callParameters;
public:
	// No variables
	LuaEntry(int callbkCoroutineIndex);
	// Yes variables
	LuaEntry(int callbkCoroutineIndex,
		int numParams, LuaInterface::LuaValue* values);
	~LuaEntry();

	void onFinish();
};


#endif