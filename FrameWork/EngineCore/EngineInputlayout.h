#pragma once

//설명 : 정점 구조에 대한 시멘틱 정보를 desc만 미리 만들어놓는 역할
class EngineInputLayoutData
{
public:
	static UINT FormatSize(DXGI_FORMAT _Format);

	void AddInputElement(
		LPCSTR _SemanticName,
		DXGI_FORMAT _Format,
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
		UINT _InstanceDataStepRate = 0,
		UINT _AlignedByteOffset = -1,
		UINT _InputSlot = 0,
		UINT _SemanticIndex = 0
	);

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> ElementDescs;
	int VertexOffset = 0;
	int InstanceOffset = 0;
};

// 설명 : 정점 구조체에 대한 메타데이터, 각 정점구조체 마다 매핑해놓기 위한 클래스
// 사용법 - 
// 사용할 버텍스에 상속한다
//ex) class VertexClass : public EngineVertexLayoutData<VertexClass>
template <typename VertexType>
class EngineVertexLayoutData
{
public:
	static EngineInputLayoutData InputLayoutData;
};

template <typename VertexType>
EngineInputLayoutData EngineVertexLayoutData<VertexType>::InputLayoutData{};



