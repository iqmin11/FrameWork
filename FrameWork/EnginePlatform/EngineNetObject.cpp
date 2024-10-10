#include "PrecompileHeader.h"
#include "EngineNetObject.h"

std::atomic<int> EngineNetObject::AtomicObjectID;
std::mutex EngineNetObject::ObjectLock;
std::map<int, EngineNetObject*> EngineNetObject::AllNetObjects;

EngineNetObject::EngineNetObject() 
{
}

EngineNetObject::~EngineNetObject() 
{
}

void EngineNetObject::InitServerObject()
{
	ObjectID = ++AtomicObjectID;
	ObjectLock.lock();
	AllNetObjects.insert(std::pair<int, EngineNetObject*>(ObjectID, this));
	ObjectLock.unlock();
	ControllType = NetControllType::UserControll;
}

void EngineNetObject::InitClientObject(int _ObjectID)
{
	ObjectID = _ObjectID;
	ObjectLock.lock();
	AllNetObjects.insert(std::pair<int, EngineNetObject*>(ObjectID, this));
	ObjectLock.unlock();
	ControllType = NetControllType::ServerControll;
}

