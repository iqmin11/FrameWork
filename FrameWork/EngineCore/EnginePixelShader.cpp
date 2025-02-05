#include "PrecompileHeader.h"
#include "EnginePixelShader.h"

#include "EngineBase/EngineFile.h"

EnginePixelShader::EnginePixelShader() 
{
}

EnginePixelShader::~EnginePixelShader() 
{
	if (ShaderBlob != nullptr)
	{
		ShaderBlob->Release();
		ShaderBlob = nullptr;
	}

	if (PixelShader != nullptr)
	{
		PixelShader->Release();
		PixelShader = nullptr;
	}
}

std::shared_ptr<EnginePixelShader> EnginePixelShader::Load(EngineFile ShaderFile, std::string_view ShaderName)
{
	std::shared_ptr<EnginePixelShader> NewPs = Create(ShaderName);

	if (NewPs == nullptr)
	{
		assert("�ȼ� ���̴� ������ �����߽��ϴ�");
	}

	NewPs->SetPath(ShaderFile);
	NewPs->ShaderCompile(ShaderFile, "ps_main", "ps_5_0");

	HRESULT Result = EngineDevice::GetDevice()->CreatePixelShader(NewPs->ShaderBlob->GetBufferPointer(), NewPs->ShaderBlob->GetBufferSize(), nullptr, &(NewPs->PixelShader));
	assert(SUCCEEDED(Result));

	return NewPs;
}

