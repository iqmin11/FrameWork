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
