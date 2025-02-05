#include "PrecompileHeader.h"
#include "EngineInputLayout.h"

#include "EngineVertexShader.h"

EngineInputLayout::EngineInputLayout() 
{
}

EngineInputLayout::~EngineInputLayout() 
{
	if (InputLayout != nullptr)
	{
		InputLayout->Release();
		InputLayout = nullptr;
	}
}

void EngineInputLayout::Load(std::string_view ILName, D3D11_INPUT_ELEMENT_DESC* ILDesc, UINT ILDescArrSize, std::shared_ptr<EngineVertexShader> Vs)
{
	if(Vs == nullptr)
	{
		assert("InputLayout을 세팅할 Vs가 nullptr입니다.");
	}

	std::shared_ptr<EngineInputLayout> NewInputLayout = EngineInputLayout::Create(ILName);

	HRESULT Result = EngineDevice::GetDevice()->CreateInputLayout(ILDesc, ILDescArrSize, Vs->GetBlob()->GetBufferPointer(), Vs->GetBlob()->GetBufferSize(), &(NewInputLayout->InputLayout));
	assert(SUCCEEDED(Result));
}

