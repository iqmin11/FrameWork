#pragma once

// 설명 :
class IEngineShader
{
public:
	// constrcuter destructer
	IEngineShader();
	virtual ~IEngineShader() = 0;

	// delete Function
	IEngineShader(const IEngineShader& _Other) = delete;
	IEngineShader(IEngineShader&& _Other) noexcept = delete;
	IEngineShader& operator=(const IEngineShader& _Other) = delete;
	IEngineShader& operator=(IEngineShader&& _Other) noexcept = delete;

	ID3DBlob* GetBlob()
	{
		if (ShaderBlob == nullptr)
		{
			assert("ShaderBlob이 nullptr입니다");
			return nullptr;
		}

		return ShaderBlob;
	}

protected:
	ID3DBlob* ShaderBlob = nullptr;

private:

};

