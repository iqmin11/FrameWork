#pragma once
#include "EngineBase/EngineFile.h"

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

	void ShaderCompile(EngineFile ShaderFile, std::string_view EntryPoint, std::string_view ShaderModel)
	{
		ID3DBlob* ShaderCompileErrorsBlob;
		HRESULT Result = D3DCompileFromFile(ShaderFile.GetFullPathToWstring().c_str(), nullptr, nullptr, EntryPoint.data(), ShaderModel.data(), 0, 0, &(ShaderBlob), &ShaderCompileErrorsBlob);
		
		if (FAILED(Result))
		{
			const char* errorString = NULL;
			if (Result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			{
				errorString = "Could not compile shader; file not found";
			}
			else if (ShaderCompileErrorsBlob)
			{
				errorString = (const char*)ShaderCompileErrorsBlob->GetBufferPointer();
				ShaderCompileErrorsBlob->Release();
			}
			MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		}
	}

protected:
	ID3DBlob* ShaderBlob = nullptr;

private:

};

