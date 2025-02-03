#include "PrecompileHeader.h"
#include "EngineVertexShader.h"

#include "EngineDevice.h"
#include "EngineBase/EngineFile.h"

EngineVertexShader::EngineVertexShader() 
{
}

EngineVertexShader::~EngineVertexShader() 
{
	if (ShaderBlob != nullptr)
	{
		ShaderBlob->Release();
		ShaderBlob = nullptr;
	}

	if (VertexShader != nullptr)
	{
		VertexShader->Release();
		VertexShader = nullptr;
	}
}

std::shared_ptr<EngineVertexShader> EngineVertexShader::Load(EngineFile ShaderFile, std::string_view ShaderName)
{
	std::shared_ptr<EngineVertexShader> NewVs = Create(ShaderName);

	if (NewVs == nullptr)
	{
		assert("버텍스 쉐이더 생성에 실패했습니다");
	}

	NewVs->SetPath(ShaderFile);

	ID3DBlob* ShaderCompileErrorsBlob;
	HRESULT Result = D3DCompileFromFile(ShaderFile.GetFullPathToWstring().c_str(), nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &(NewVs->ShaderBlob), &ShaderCompileErrorsBlob);

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
		return nullptr;
	}

	Result = EngineDevice::GetDevice()->CreateVertexShader(NewVs->ShaderBlob->GetBufferPointer(), NewVs->ShaderBlob->GetBufferSize(), nullptr, &(NewVs->VertexShader));
	assert(SUCCEEDED(Result));

	return NewVs;
}

