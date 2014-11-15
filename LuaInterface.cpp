#include "LuaInterface.h"
#include "MoveProcess.h"
#include "WaitProcess.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "LuaEntry.h"

union LuaValue;
// Actual C bindings here

extern "C"
{
	// Accepts one argument.
	// LuaInterface:wait(coroutine, 500 milliseconds)
	static int wait(lua_State* L)
	{
		assert(lua_gettop(L) == 3);
		int coroutineIndex = luaL_checkint(L, 2);
		int waitTimeMs = luaL_checkint(L, 3);

		// Make process
		WaitProcess* p = new WaitProcess(coroutineIndex, waitTimeMs);
		Services::processManager()->addProcess(p);

		return 0;
	}

	// returns int
	// newCoroutine(functionName)
	static int newThread(lua_State* L)
	{
		assert(lua_gettop(L) == 2);
		string functionName = luaL_checkstring(L, 2);

		// Grab my LuaInterface instance
		LuaInterface** luaInterface = static_cast<LuaInterface**>(
			luaL_checkudata(L, 1, "LuaInterfaceMT")
			);

		// Run the function from LuaInterface
		int coroutineIndex = (*luaInterface)->newCoroutine(functionName);

		// Return the new index we have
		lua_pushinteger(L, coroutineIndex);
		return 1;

	}

	// Create a process to start it then put it at the end, so the order works
	// startCoroutine(int coroutineID, ... )
	static int startCoroutine(lua_State* L)
	{
		// So this depends on the number of values
		int top = lua_gettop(L);
		int coroutineIndex = lua_tointeger(L, 2);
		LuaEntry* entryProcess;

		// so say there are 3 parameters, 2 of them
		// are to be preserved.
		// that means top = 4. L-1 is useless, L-2 is 
		// and L-3 and L-4 are the good ones.
		// so the # of parameters is top - 2 
		if (top > 2)
		{
			LuaInterface::LuaValue* values =
				new LuaInterface::LuaValue[top - 2];
			int index = 0;
			for (int i = 3; i <= top; i++)
			{
				if (lua_type(L, i) == LUA_TNUMBER)
				{
					double n = lua_tonumber(L, i);
					cout << "number: " << n << endl;
					values[index].Type = LuaInterface::LuaValue::DOUBLE;
					values[index].d = n;
				} 
				else if (lua_isstring(L, i))
				{
					string s = lua_tostring(L, i);
					cout << "string " << s << endl;
					values[index].Type = LuaInterface::LuaValue::STRING;
					values[index].s = s;
				}
				index++;
			}
			cout << "fine" << endl;
			entryProcess = new LuaEntry(coroutineIndex,
				top - 2, values);
		} 
		else
		{
			// No parameters?
			entryProcess = new LuaEntry(coroutineIndex);
		}

		Services::processManager()->addProcess(entryProcess);

		return 0;
	}

	// moveEntity(coroutineIndex, objID, vx, vy, distance)
	static int moveEntity(lua_State* L)
	{
		// Grab my parameters
		assert(lua_gettop(L) == 6);
		int coroutineIndex = luaL_checkint(L, 2);
		int objectID = luaL_checkint(L, 3);
		float vx = (float)luaL_checknumber(L, 4);
		float vy = (float)luaL_checknumber(L, 5);
		float distance = (float)luaL_checknumber(L, 6);

		MoveProcess *p = new MoveProcess
			(coroutineIndex, objectID, distance, vx, vy);
		Services::processManager()->addProcess(p);

		return 0;
	}

	// objID = newEntity(initialx, y, vx, vy);
	static int newEntity(lua_State* L)
	{
		//  Grab parameters
		assert(lua_gettop(L) == 5);
		float x = luaL_checknumber(L, 2);
		float y = luaL_checknumber(L, 3);
		float vx = luaL_checknumber(L, 4);
		float vy = luaL_checknumber(L, 5);

		// I will refactor this into a factory class at some point
		// or the pattern that clones things
		PhysicsComponent* p = new PhysicsComponent(x, y, vx, vy);
		AnimationComponent* a = new AnimationComponent(Services::resourceManager(),
			"creep2green");

		ComponentManager* componentManager = Services::componentManager();
		componentManager->addComponent(p, ComponentType::PHYSICS);
		componentManager->addComponent(a, ComponentType::ANIMATION);
		cout << "constructoing" << endl;

		vector<Component*> v;
		v.push_back(p);
		v.push_back(a);
		int newobj = componentManager->newGameObject(v);

		// return ID of the new thing
		lua_pushinteger(L, newobj);

		return 1;
	}

	// increment the reference Counts of provided objID
	static int registerDependency(lua_State* L)
	{
		// In the future maybe we can track the thing
		// that registers it, for now it's just a simple incrementation
		assert(lua_gettop(L) == 2);
		int objID = luaL_checkint(L, 2);

		// Register targetObjectID as an object being used.
		Services::componentManager()->gameObjRegisterDependency(objID);

		return 0;
	}

	// decrement the reference Counts of provided objID
	static int removeDependency(lua_State* L)
	{
		// Same comment, this can be more sophisticated in future
		assert(lua_gettop(L) == 2);
		int objID = luaL_checkint(L, 2);

		Services::componentManager()->gameObjRemoveDependency(objID);

		return 0;
	}
}

LuaInterface::LuaInterface()
{
	// Library init
	L = luaL_newstate();
	luaL_openlibs(L);

	// Register this class
	std::cout << "Registering LuaInterface" << std::endl;
	luaL_newmetatable(L, "LuaInterfaceMT");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index"); // ListMT .__index = ListMT

	lua_pushcfunction(L, wait);
	lua_setfield(L, -2, "wait");

	lua_pushcfunction(L, newThread);
	lua_setfield(L, -2, "newThread");

	lua_pushcfunction(L, moveEntity);
	lua_setfield(L, -2, "moveEntity");

	lua_pushcfunction(L, newEntity);
	lua_setfield(L, -2, "newEntity");

	lua_pushcfunction(L, startCoroutine);
	lua_setfield(L, -2, "startCoroutine");

	lua_pushcfunction(L, registerDependency);
	lua_setfield(L, -2, "registerDependency");

	lua_pushcfunction(L, removeDependency);
	lua_setfield(L, -2, "removeDependency");


	LuaInterface** thisInterface = static_cast<LuaInterface**>(
		lua_newuserdata(L, sizeof(LuaInterface*))
		);
	*(thisInterface) = this;
	luaL_setmetatable(L, "LuaInterfaceMT");  // set metatable for this
	// LuaInterface in Lua will address this instance of LuaInterface now.
	lua_setglobal(L, "LuaInterface");



}

LuaInterface::~LuaInterface()
{
	lua_close(L);
}

// returns the index of the coroutine
int LuaInterface::newCoroutine(string functionName)
{
	lua_getglobal(L, "newCoroutine");
	lua_pushstring(L, functionName.c_str());
	lua_call(L, 1, 1);
	int coroutineIndex = lua_tointeger(L, -1);
	lua_pop(L, 1);

	return coroutineIndex;
}


void LuaInterface::resumeCoroutine(int coroutineIndex)
{
	lua_getglobal(L, "resumeCoroutine");
	lua_pushinteger(L, coroutineIndex);

	// To-do: getting variables back, ofc
	lua_call(L, 1, 0);
}

// I am aware using pointers here might make memory management tricky
// Any class which uses resumeCoroutine is responsible for delete[]ing the LuaValue*
// it gets back. Also... notice how there is NO checking to make sure you didn't
// provide the wrong number of parameters. In a later version of the engine, 
// that needs to be addressed. 

// A generalized lua function call method.
// Do note that you can pass it ints, but it only returns doubles
// Returns NULL if something went wrong
LuaInterface::LuaValue* LuaInterface::resumeCoroutine(int coroutineIndex, int numResults,
	int numParameters, LuaInterface::LuaValue* params)
{
	lua_getglobal(L, "resumeCoroutine");
	lua_pushinteger(L, coroutineIndex);
	for (int i = 0; i < numParameters; i++)
	{
		switch (params[i].Type)
		{
		case LuaInterface::LuaValue::DOUBLE:
			cout << "Pushing double" << endl;
			lua_pushnumber(L, params[i].d);
			break;
		case LuaInterface::LuaValue::STRING:
			cout << "Pushing string" << endl;
			lua_pushstring(L, params[i].s.c_str());
			break;
		case LuaInterface::LuaValue::INT:
			cout << "Pushing int" << endl;
			lua_pushinteger(L, params[i].i);
			break;
		}
	}

	// parameters + 1 to include the name, "resumeCoroutine"
	// numResults + 1 because the first one is "true" or "false"
	lua_call(L, numParameters + 1, numResults + 1);
	
	// If it didn't work, just return NULL
	bool success = lua_toboolean(L, -1);
	if (!success) return NULL;

	// get the results
	LuaValue* result = new LuaValue[numResults];
	int index = 0;
	for (int i = numResults; i > 0; i--)
	{
		if (lua_isstring(L, -i))
		{
			string s = lua_tostring(L, -i);
			result[index].Type = LuaInterface::LuaValue::STRING;
			result[index].s = s;
		}
		else if (lua_isnumber(L, -i))
		{
			double n = lua_tonumber(L, -i);
			result[index].Type = LuaInterface::LuaValue::DOUBLE;
			result[index].d = n;
		}
		index++;
	}

	cout << "made the call " << endl;
	// Do not forget to pop results off stack
	lua_pop(L, numResults + 1);
	return result;

}
