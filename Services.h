// If we're going to have a global, let's at least centralise it 
// and make it neat.

#ifndef SERVICES_H
#define SERVICES_H

#include "LuaInterface.h"
class LuaInterface;
#include "ProcessManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "ComponentManager.h"

class Services
{
private:
	// Services
	static ProcessManager*		processManager_;
	static ResourceManager*		resourceManager_;
	static LuaInterface*		luaInterface_;
	static LogManager*			logManager_;
	static ComponentManager*	componentManager_;
public:

	// Providers
	static void provide(ProcessManager* processManager)
	{
		processManager_ = processManager;
	}
	static void provide(ResourceManager* resourceManager)
	{
		resourceManager_ = resourceManager;
	}
	static void provide(LuaInterface* luaInterface)
	{
		luaInterface_ = luaInterface;
	}
	static void provide(LogManager* logManager)
	{
		logManager_ = logManager;
	}
	static void provide(ComponentManager* componentManager)
	{
		componentManager_ = componentManager;
	}

	// Getters
	static ProcessManager* processManager() { return processManager_; }
	static ResourceManager* resourceManager() { return resourceManager_; }
	static LuaInterface* luaInterface() { return luaInterface_; }
	static LogManager* logManager() { return logManager_; }
	static ComponentManager* componentManager() { return componentManager_; }

};

#endif