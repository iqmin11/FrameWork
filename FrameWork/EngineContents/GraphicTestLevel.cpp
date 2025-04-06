#include "PrecompileHeader.h"
#include "GraphicTestLevel.h"
#include "TestActor.h"

GraphicTestLevel::GraphicTestLevel() 
{
}

GraphicTestLevel::~GraphicTestLevel() 
{
}

void GraphicTestLevel::Begin()
{
	MyTestActor = EngineLevel::CreateActor<TestActor>();
}

