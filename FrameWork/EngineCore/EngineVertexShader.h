#pragma once
#include "EngineResorce.h"
#include "IEngineShader.h"

// Ό³Έν :
class EngineVertexShader : public EngineResorce<EngineVertexShader>, public IEngineShader
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

	ID3D11VertexShader* GetVertexShader()
	{
		return VertexShader;
	}
	
protected:

private:
	ID3D11VertexShader* VertexShader = nullptr;
};

