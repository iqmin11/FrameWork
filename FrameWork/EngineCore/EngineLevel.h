#pragma once
#include "EngineActor.h"
#include "EngineCore.h"

class EngineActor;
class EngineLevel : public EngineObject
{
	friend EngineCore;
public:
	EngineLevel();
	~EngineLevel();

	// delete Function
	EngineLevel(const EngineLevel& _Other) = delete;
	EngineLevel(EngineLevel&& _Other) noexcept = delete;
	EngineLevel& operator=(const EngineLevel& _Other) = delete;
	EngineLevel& operator=(EngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(int _Order = 0, const std::string_view& _Name = "")
	{
		std::shared_ptr<EngineActor> NewActor = std::make_shared<ActorType>();

		std::string Name = _Name.data();

		if (_Name == "")
		{
			const type_info& Info = typeid(ActorType);
			Name = Info.name();
			Name.replace(0, 6, "");
		}

		ActorInit(NewActor, _Order);

		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

protected:
	void Begin() override;
	virtual void OnLevelEnter();
	void Tick(float DeltaTime) override;
	virtual void OnLevelExit();

private:
	std::map<int, std::vector<std::shared_ptr<EngineActor>>> Actors;
	void ActorInit(std::shared_ptr<EngineActor> _Actor, int _Order);

	void ActorUpdate(float DeltaTime);
	void ActorTransformUpdate(float DeltaTime);
	void ActorLateUpdate(float DeltaTime);
	void ActorRelease();
};