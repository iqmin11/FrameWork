#pragma once
#include "EngineResorce.h"
#include "IEngineShader.h"

// Ό³Έν :
class EnginePixelShader : public EngineResorce<EnginePixelShader>, public IEngineShader 
{
public:
	// constrcuter destructer
	EnginePixelShader();
	~EnginePixelShader();

	// delete Function
	EnginePixelShader(const EnginePixelShader& _Other) = delete;
	EnginePixelShader(EnginePixelShader&& _Other) noexcept = delete;
	EnginePixelShader& operator=(const EnginePixelShader& _Other) = delete;
	EnginePixelShader& operator=(EnginePixelShader&& _Other) noexcept = delete;

	static std::shared_ptr<EnginePixelShader> Load(class EngineFile ShaderFile, std::string_view ShaderName);

	ID3D11PixelShader* GetPixelShader()
	{
		return PixelShader;
	}

protected:

private:
	ID3D11PixelShader* PixelShader = nullptr;

};

