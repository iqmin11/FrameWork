#pragma once
#include <EngineCore/EngineCore.h>

class ContentsCore : public EngineCore
{
public:
	// construtor destructor
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

	static void ContentsBegin();
	static void ContentsEnd();

protected:


private:

};

