#pragma once

class EngineInputLayoutInfo
{
public:
	static UINT FormatSize(DXGI_FORMAT _Format);

	std::vector<D3D11_INPUT_ELEMENT_DESC>& GetDescs()
	{
		return Descs;
	}

	void AddInputLayOut(
		LPCSTR SemanticName, 
		DXGI_FORMAT Format, 
		D3D11_INPUT_CLASSIFICATION InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, 
		UINT InputSlot = 0,
		UINT SemanticIndex = 0
	);

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
	int Offset = 0;

};

// Ό³Έν :
struct EngineVertex
{
	static EngineInputLayoutInfo LayOutInfo;

	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
};

