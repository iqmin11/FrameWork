#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include "ChatLevel.h"
#include "GraphicTestLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::ContentsBegin()
{
	CreateLevel<GraphicTestLevel>();
	ChangeLevel("GraphicTestLevel");
}

void ContentsCore::ContentsEnd()
{

}
