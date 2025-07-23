#pragma once
#include "EngineInputLayout.h"

// ���� :
class EngineDynamicMeshVertex : public EngineVertexLayoutData<EngineDynamicMeshVertex>
{
public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
	float4 NORMAL;
	float4 BINORMAL;
	float4 TANGENT;
	float4 WEIGHT;
	int BLENDINDICES[4];
};

