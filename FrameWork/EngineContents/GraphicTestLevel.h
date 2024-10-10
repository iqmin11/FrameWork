#pragma once
#include "EngineCore/EngineLevel.h"

// Ό³Έν :
class GraphicTestLevel : public EngineLevel
{
public:
	// constrcuter destructer
	GraphicTestLevel();
	~GraphicTestLevel();

	// delete Function
	GraphicTestLevel(const GraphicTestLevel& _Other) = delete;
	GraphicTestLevel(GraphicTestLevel&& _Other) noexcept = delete;
	GraphicTestLevel& operator=(const GraphicTestLevel& _Other) = delete;
	GraphicTestLevel& operator=(GraphicTestLevel&& _Other) noexcept = delete;

protected:

private:

};

