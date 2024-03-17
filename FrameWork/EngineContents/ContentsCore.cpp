#include "ContentsCore.h"
#include "TestLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::ContentsBegin()
{
	CreateLevel<TestLevel>();
	ChangeLevel("TestLevel");
}

void ContentsCore::ContentsEnd()
{

}
