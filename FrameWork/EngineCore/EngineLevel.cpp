#include "PrecompileHeader.h"
#include "EngineLevel.h"
#include "EngineGUI.h"
#include "EngineRenderer.h"

EngineLevel::EngineLevel()
{

}

EngineLevel::~EngineLevel()
{

}

void EngineLevel::PushRenderer(std::shared_ptr<EngineRenderer> Renderer)
{
	if (Renderer == nullptr)
	{
		MsgAssert("Renderer == nullptr");
	}

	Renderers[Renderer->GetOrder()].emplace_back(Renderer);
}


void EngineLevel::Begin()
{
}

void EngineLevel::OnLevelEnter()
{
}

void EngineLevel::Tick(float DeltaTime)
{
	EngineGUI::Tick(DeltaTime, std::static_pointer_cast<EngineLevel>(this->shared_from_this()));
}

void EngineLevel::OnLevelExit()
{
}

void EngineLevel::ActorInit(std::shared_ptr<EngineActor> _Actor, int _Order)
{
	this->Actors[_Order].push_back(_Actor);
	_Actor->Init_Internal(SharedCastingThis<EngineLevel>());
	_Actor->Begin();
}

void EngineLevel::ActorUpdate(float DeltaTime)
{
	auto GroupEndIter = Actors.end();

	for (auto GroupStartIter = Actors.begin(); GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::vector<std::shared_ptr<EngineActor>>& ActorGroup = GroupStartIter->second;
		size_t CurActorGroupSize = ActorGroup.size();

		for (int i = 0; i < CurActorGroupSize; ++i)
		{
			ActorGroup[i]->Tick(DeltaTime);
		}
	}
}

void EngineLevel::ActorTransformUpdate(float DeltaTime)
{
	auto GroupEndIter = Actors.end();

	for (auto GroupStartIter = Actors.begin(); GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::vector<std::shared_ptr<EngineActor>>& ActorGroup = GroupStartIter->second;
		size_t CurActorGroupSize = ActorGroup.size();

		for (int i = 0; i < CurActorGroupSize; ++i)
		{
			ActorGroup[i]->GetTransformRef().TransformUpdate();
		}
	}
}

void EngineLevel::ActorLateUpdate(float DeltaTime)
{
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
