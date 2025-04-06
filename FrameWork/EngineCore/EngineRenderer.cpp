#include "PrecompileHeader.h"
#include "EngineRenderer.h"
#include "EngineLevel.h"

EngineRenderer::EngineRenderer() 
{
}

EngineRenderer::~EngineRenderer() 
{
}

void EngineRenderer::Begin()
{
	GetOwnerLevel()->PushRenderer(SharedCastingThis<EngineRenderer>());
}

