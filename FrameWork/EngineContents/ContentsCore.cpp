#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include "ChatLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::ContentsBegin()
{
	CreateLevel<ChatLevel>();
	ChangeLevel("ChatLevel");
}

void ContentsCore::ContentsEnd()
{

}
