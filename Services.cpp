#include "Services.h"

// Default initializations of the static fields.
ProcessManager* Services::processManager_ = NULL;
ResourceManager* Services::resourceManager_ = NULL;
LuaInterface* Services::luaInterface_ = NULL;
LogManager* Services::logManager_ = NULL;
ComponentManager* Services::componentManager_ = NULL;