#pragma once

// Ό³Έν :
class EngineShader
{
public:
	// constrcuter destructer
	EngineShader();
	~EngineShader();

	// delete Function
	EngineShader(const EngineShader& _Other) = delete;
	EngineShader(EngineShader&& _Other) noexcept = delete;
	EngineShader& operator=(const EngineShader& _Other) = delete;
	EngineShader& operator=(EngineShader&& _Other) noexcept = delete;

	ID3DBlob* GetBlob()
	{
		return ShaderBlob;
	}

protected:

private:
	ID3DBlob* ShaderBlob = nullptr;

};

