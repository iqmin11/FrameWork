#include "PrecompileHeader.h"
#include "EngineLevel.h"
#include "EngineGUI.h"

EngineLevel::EngineLevel()
{

}

EngineLevel::~EngineLevel()
{

}

void EngineLevel::Begin()
{
}

void EngineLevel::Tick(float DeltaTime)
{
	EngineGUI::Tick(DeltaTime, std::static_pointer_cast<EngineLevel>(this->shared_from_this()));
}

void EngineLevel::ActorInit(std::shared_ptr<EngineActor> _Actor, int _Order)
{
	this->Actors[_Order].push_back(_Actor);
	_Actor->Begin();
}

void EngineLevel::ActorUpdate(float _DeltaTime)
{
	{
		// 이건 나중에 만들어질 랜더러의 랜더가 다 끝나고 되는 랜더가 될겁니다.
		std::map<int, std::vector<std::shared_ptr<EngineActor>>>::iterator GroupEndIter = Actors.end();

		for (auto GroupStartIter = Actors.begin(); GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::vector<std::shared_ptr<EngineActor>>& ActorList = GroupStartIter->second;

			std::vector<std::shared_ptr<EngineActor>>::iterator ActorEnd = ActorList.end();

			for (auto ActorStart = ActorList.begin(); ActorStart != ActorEnd; ++ActorStart)
			{
				std::shared_ptr<EngineActor>& Actor = *ActorStart;

				Actor->Tick(_DeltaTime);
			}
		}
	}
}

void EngineLevel::ActorRelease()
{
	{
		std::map<int, std::vector<std::shared_ptr<EngineActor>>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::vector<std::shared_ptr<EngineActor>>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::vector<std::shared_ptr<EngineActor>>& ActorList = GroupStartIter->second;

			std::vector<std::shared_ptr<EngineActor>>::iterator ActorStart = ActorList.begin();
			std::vector<std::shared_ptr<EngineActor>>::iterator ActorEnd = ActorList.end();

			for (; ActorStart != ActorEnd; )
			{
				std::shared_ptr<EngineActor> RelaseActor = (*ActorStart);

				if (nullptr != RelaseActor && false == RelaseActor->IsDeath())
				{
					++ActorStart;
					continue;
				}

				ActorStart = ActorList.erase(ActorStart);
			}
		}
	}
}
