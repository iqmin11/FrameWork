#include "PrecompileHeader.h"
#include "EngineVertexShader.h"

#include "EngineDevice.h"
#include "EngineBase/EngineFile.h"

EngineVertexShader::EngineVertexShader() 
{
}

EngineVertexShader::~EngineVertexShader() 
{
}

void EngineVertexShader::Load(EngineFile ShaderFile, std::string_view ShaderName)
{
	std::shared_ptr<EngineVertexShader> NewVs = Create(ShaderName);

	if (NewVs == nullptr)
	{
		assert("버텍스 쉐이더 생성에 실패했습니다");
	}

	NewVs->SetPath(ShaderFile);

	ID3DBlob* ShaderCompileErrorsBlob;
	HRESULT Result = D3DCompileFromFile(ShaderFile.GetFullPathToWstring().c_str(), nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &(NewVs->VsBlob), &ShaderCompileErrorsBlob);

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
		return;
	}

	Result = EngineDevice::GetDevice()->CreateVertexShader(NewVs->VsBlob->GetBufferPointer(), NewVs->VsBlob->GetBufferSize(), nullptr, &(NewVs->VertexShader));
	assert(SUCCEEDED(Result));

}

