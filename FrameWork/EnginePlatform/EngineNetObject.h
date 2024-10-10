#pragma once
#include <mutex>

enum class NetControllType
{
	None,
	UserControll,
	ServerControll,
};

// Ό³Έν :
class EngineNetObject
{
public:
	// constrcuter destructer
	EngineNetObject();
	~EngineNetObject();

	// delete Function
	EngineNetObject(const EngineNetObject& _Other) = delete;
	EngineNetObject(EngineNetObject&& _Other) noexcept = delete;
	EngineNetObject& operator=(const EngineNetObject& _Other) = delete;
	EngineNetObject& operator=(EngineNetObject&& _Other) noexcept = delete;

	void InitServerObject();

	void InitClientObject(int _ObjectID);

	void SetControll(NetControllType _ControllType)
	{
		ControllType = _ControllType;
	}

	NetControllType  GetControllType() const
	{
		return ControllType;
	}

protected:

private:
	static std::atomic<int> AtomicObjectID;
	static std::mutex ObjectLock;
	static std::map<int, EngineNetObject*> AllNetObjects;

	NetControllType ControllType = NetControllType::None;
	int ObjectID = -1;

};

