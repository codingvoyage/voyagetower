#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H

#include <assert.h>
#include <lua.hpp>
#include <iostream>
#include <string>

#include "Services.h"
#include "LuaCallbackProcess.h"
#include <string>

using namespace std;

class LuaInterface
{

public:

	// Yeah.  
	class LuaValue
	{
	public:
		string		s;
		int			i;
		double		d;

		enum
		{
			STRING, INT, DOUBLE
		} Type;
	};


	lua_State*				L;
	LuaInterface();
	~LuaInterface();


	int newCoroutine(string functionName);
	void resumeCoroutine(int coroutineIndex);
	LuaValue* resumeCoroutine(int coroutineIndex, int numResults,
		int numParameters, LuaValue* params);


};





#endif
