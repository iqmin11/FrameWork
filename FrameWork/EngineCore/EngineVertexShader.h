#pragma once
#include "EngineResorce.h"

// Ό³Έν :
class EngineVertexShader : public EngineResorce<EngineVertexShader>
{
public:
	// constrcuter destructer
	EngineVertexShader();
	~EngineVertexShader();

	// delete Function
	EngineVertexShader(const EngineVertexShader& _Other) = delete;
	EngineVertexShader(EngineVertexShader&& _Other) noexcept = delete;
	EngineVertexShader& operator=(const EngineVertexShader& _Other) = delete;
	EngineVertexShader& operator=(EngineVertexShader&& _Other) noexcept = delete;

	static void Load(class EngineFile ShaderFile, std::string_view ShaderName);
	
protected:

private:
	ID3DBlob* VsBlob = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;

};

