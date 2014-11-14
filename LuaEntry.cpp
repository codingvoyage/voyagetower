#include "LuaEntry.h"
#include "Services.h"

// No variables
LuaEntry::LuaEntry(int callbkCoroutineIndex) :
	LuaCallbackProcess(callbkCoroutineIndex)
{
	deactivate();
	callParameters = 0;
	callValues = NULL;
}

// Yes variables
LuaEntry::LuaEntry(int callbkCoroutineIndex, 
	int numParams,
	LuaInterface::LuaValue* values) :
	LuaCallbackProcess(callbkCoroutineIndex)
{
	deactivate();
	callParameters = numParams;
	callValues = values;
}

LuaEntry::~LuaEntry() {}


void LuaEntry::onFinish()
{
	// 
	if (callValues != NULL)
	{
		cout << "call parameters: " << callParameters << endl;
		// Processes don't return results, so that's 0
		Services::luaInterface()->resumeCoroutine
			(coroutineIndex, 0, callParameters, callValues);
		delete[] callValues;
		// Note - nasty _BLOCK_TYPE_IS_VALID(phead->nBlockUse) error happens
		// if you use delete instead of delete[] 
		//delete callValues;
	} 
	else 
	{
		LuaCallbackProcess::onFinish();
	}
}
