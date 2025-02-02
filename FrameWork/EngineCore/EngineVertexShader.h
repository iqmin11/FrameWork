#pragma once
#include "EngineResorce.h"
#include "EngineShader.h"

// Ό³Έν :
class EngineVertexShader : public EngineResorce<EngineVertexShader>, public EngineShader
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

	static std::shared_ptr<EngineVertexShader> Load(class EngineFile ShaderFile, std::string_view ShaderName);

	ID3DBlob* GetBlob()
	{
		return VsBlob;
	}

	ID3D11VertexShader* GetVs()
	{
		return VertexShader;
	}
	
protected:

private:
	ID3DBlob* VsBlob = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;
};

