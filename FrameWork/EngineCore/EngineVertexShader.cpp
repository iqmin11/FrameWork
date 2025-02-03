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
		assert("���ؽ� ���̴� ������ �����߽��ϴ�");
	}

	NewVs->SetPath(ShaderFile);
	NewVs->ShaderCompile(ShaderFile, "vs_main", "vs_5_0");

	HRESULT Result = EngineDevice::GetDevice()->CreateVertexShader(NewVs->ShaderBlob->GetBufferPointer(), NewVs->ShaderBlob->GetBufferSize(), nullptr, &(NewVs->VertexShader));
	assert(SUCCEEDED(Result));

	return NewVs;
}

