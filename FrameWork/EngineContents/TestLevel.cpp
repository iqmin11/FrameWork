#include "PrecompileHeader.h"
#include "TestLevel.h"
#include "EngineCore/EngineGUI.h"
#include "TestGUI.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

void TestLevel::Begin()
{
	EngineGUI::GUIWindowCreate<TestGUI>("TestWindow");
	int a = 0;
}

void TestLevel::Tick(float DeltaTime)
{
	EngineLevel::Tick(DeltaTime);
	int a = 0;
}
