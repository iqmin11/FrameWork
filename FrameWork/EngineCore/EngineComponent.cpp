#include "PrecompileHeader.h"
#include "EngineComponent.h"

EngineComponent::EngineComponent()
{

}

EngineComponent::~EngineComponent()
{

}

const std::shared_ptr<class EngineObject> EngineComponent::GetParent()
{
	return GetTransformRef().GetParent()->GetMaster();
}

void EngineComponent::Begin()
{
}