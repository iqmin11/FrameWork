#pragma once
#include "EngineResorce.h"

// Ό³Έν :
class EngineInputLayout : public EngineResorce<EngineInputLayout>
{
public:
	// constrcuter destructer
	EngineInputLayout();
	~EngineInputLayout();

	// delete Function
	EngineInputLayout(const EngineInputLayout& _Other) = delete;
	EngineInputLayout(EngineInputLayout&& _Other) noexcept = delete;
	EngineInputLayout& operator=(const EngineInputLayout& _Other) = delete;
	EngineInputLayout& operator=(EngineInputLayout&& _Other) noexcept = delete;

	static std::shared_ptr<EngineInputLayout> Load(std::string_view ILName, const D3D11_INPUT_ELEMENT_DESC* ILDesc, UINT ILDescArrSize, std::shared_ptr<class EngineVertexShader> Vs);
	ID3D11InputLayout* GetIL()
	{
		return InputLayout;
	}

protected:

private:

	ID3D11InputLayout* InputLayout = nullptr;

};

