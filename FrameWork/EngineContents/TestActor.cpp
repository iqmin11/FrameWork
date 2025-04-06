#include "PrecompileHeader.h"
#include "TestActor.h"

#include <EngineCore/EngineRenderer.h>

TestActor::TestActor() 
{
}

TestActor::~TestActor() 
{
}

void TestActor::Begin()
{
	RendererComp = CreateComponent<EngineRenderer>();
	int a = 0;
}

void TestActor::Tick(float DeltaTime)
{
	int a = 0;
}

