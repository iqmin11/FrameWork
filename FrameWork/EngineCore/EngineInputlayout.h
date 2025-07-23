#pragma once

//���� : ���� ������ ���� �ø�ƽ ������ desc�� �̸� �������� ����
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

// ���� : ���� ����ü�� ���� ��Ÿ������, �� ��������ü ���� �����س��� ���� Ŭ����
// ���� - 
// ����� ���ؽ��� ����Ѵ�
//ex) class VertexClass : public EngineVertexLayoutData<VertexClass>
template <typename VertexType>
class EngineVertexLayoutData
{
public:
	static EngineInputLayoutData InputLayoutData;
};

template <typename VertexType>
EngineInputLayoutData EngineVertexLayoutData<VertexType>::InputLayoutData{};



