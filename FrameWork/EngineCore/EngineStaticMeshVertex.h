#pragma once
#include "EngineInputLayout.h"

// Ό³Έν :
class EngineStaticMeshVertex : public EngineVertexLayoutData<EngineStaticMeshVertex>
{
public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
	float4 NORMAL;
	float4 BINORMAL;
	float4 TANGENT;
};

