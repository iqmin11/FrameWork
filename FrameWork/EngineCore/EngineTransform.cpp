#include "PrecompileHeader.h"
#include "EngineTransform.h"

EngineTransform::EngineTransform() 
{
}

EngineTransform::~EngineTransform() 
{
}

void EngineTransform::CalLocalTransform()
{
	LocalMatrix = float4x4::Compose(Scale, Rotation, Position);
}

void EngineTransform::CalWorldTransform()
{
	if (Parent == nullptr)
	{
		WorldMatrix = LocalMatrix;
		return;
	}

	WorldMatrix = LocalMatrix * Parent->WorldMatrix;
}

