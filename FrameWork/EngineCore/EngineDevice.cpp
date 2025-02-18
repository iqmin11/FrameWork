#include "PrecompileHeader.h"
#include "EngineDevice.h"

#include "EngineBase/EngineDirectory.h"
#include "EngineBase/EngineFile.h"

#include "EnginePlatform/EngineWindow.h"

#include "EngineResorce.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineInputLayout.h"


ID3D11Device1* EngineDevice::Device = nullptr;
ID3D11DeviceContext1* EngineDevice::Context = nullptr;
IDXGISwapChain1* EngineDevice::SwapChain = nullptr;
ID3D11Texture2D* EngineDevice::BackBuffer = nullptr;
ID3D11RenderTargetView* EngineDevice::MainRTV = nullptr;
ID3D11Texture2D* EngineDevice::DepthStencileBuffer = nullptr;
ID3D11DepthStencilView* EngineDevice::MainDSV = nullptr;

EngineDevice::EngineDevice()
{
}

EngineDevice::~EngineDevice()
{
}

void EngineDevice::Draw()
{
	FLOAT backgroundColor[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
	Context->ClearRenderTargetView(GetRTV(), backgroundColor);

	RECT winRect;
	GetClientRect(EngineWindow::GethWnd(), &winRect);
	D3D11_VIEWPORT viewport = { 0.0f, 0.0f, (FLOAT)(winRect.right - winRect.left), (FLOAT)(winRect.bottom - winRect.top), 0.0f, 1.0f };
	Context->RSSetViewports(1, &viewport);

	Context->OMSetRenderTargets(1, &MainRTV, nullptr);

	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Context->IASetInputLayout(EngineInputLayout::Find("Pos4_Tex4_Col4")->GetIL());

	Context->VSSetShader(EngineVertexShader::Find("vs_main")->GetVs(), nullptr, 0);
	Context->PSSetShader(EnginePixelShader::Find("ps_main")->GetPs(), nullptr, 0);

	std::shared_ptr<EngineVertexBuffer> EngineVb = EngineVertexBuffer::Find("Rect");
	
	EngineVb->Setting();
	Context->Draw(EngineVb->GetNumVerts(), 0);

	SwapChain->Present(1, 0);
}

IDXGIAdapter* EngineDevice::GetHighPerformanceAdapter()
{
	// GDI+ DXGI <=

	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// c++���� �����ϴ� Ŭ������ �����ϱ� ���� GUI�� ������ 
	// 
	// MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
		return nullptr;
	}

	size_t prevAdapterVideoMemory = 0;

	for (UINT Adapterindex = 0; ; Adapterindex++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Adapterindex, &CurAdapter);
		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (prevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			prevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();

	return Adapter;

}

void EngineDevice::CreateSwapChain()
{
	//SwapChain ��ü ���� Process
	{
		//Dxgi���丮 ��ü ����
		IDXGIFactory2* DxgiFactory;
		{
			//���丮�� ������ ���� ���� ����
			//1. Device�� ����dxgiDevice�� �������
			//2. dxgiDevice�� ���� dxgiAdapter�� �������
			//3. DxgiAdapter�� ���� Factory�� ������ ��

			//DxgiDevice ��ü�� Device�� ���� �޾ƿ�.
			IDXGIDevice1* DxgiDevice;
			HRESULT Result = Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&DxgiDevice);
			assert(SUCCEEDED(Result));

			//DxgiDevice�� ���� DxgiAdapter�� �޾ƿ�
			IDXGIAdapter* DxgiAdapter;
			Result = DxgiDevice->GetAdapter(&DxgiAdapter);
			assert(SUCCEEDED(Result));
			DxgiDevice->Release();

			//DxgiAdapter�� ���� AdapterDesc�� �޾ƿ�
			DXGI_ADAPTER_DESC AdapterDesc;
			DxgiAdapter->GetDesc(&AdapterDesc);

			//���� � �׷��� ����̽�(�׷���ī��)�� ����ϴ��� �����
			OutputDebugStringA("Graphics Device: ");
			OutputDebugStringW(AdapterDesc.Description);

			//�ش� ������� ���丮�� �������(�θ�)
			Result = DxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&DxgiFactory);
			assert(SUCCEEDED(Result));

			//����� ������
			DxgiAdapter->Release();
		}

		//Swapchain�� ���� Desc�� �����ϰ�
		DXGI_SWAP_CHAIN_DESC1 SwapChainDesc = { 0, };

		SwapChainDesc.Width = 0;
		SwapChainDesc.Height = 0;
		SwapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.BufferCount = 2;
		SwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		SwapChainDesc.Flags = 0;

		//Factory�� ����, Swapchain�� ����
		HRESULT Result = DxgiFactory->CreateSwapChainForHwnd(Device, EngineWindow::GethWnd(), &SwapChainDesc, 0, 0, &SwapChain);
		assert(SUCCEEDED(Result));

		//Swapchain�� ����µ� �����ϸ� Factory�� Release;
		DxgiFactory->Release();
	}
	
	//Swapchain�� FrameBuffer ����
	{
		//FrameBuffer �޾ƿ���
		HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		assert(SUCCEEDED(Result));

		Result = Device->CreateRenderTargetView(BackBuffer, nullptr, &MainRTV);
		assert(SUCCEEDED(Result));
		
		BackBuffer->Release();
		BackBuffer = nullptr;
	}
}

void EngineDevice::CreateResorces()
{
	//Find Shader File Path
	EngineDirectory ShaderDir;
	ShaderDir.MoveParentToChildPath("EngineCoreShader");
	ShaderDir.TryMove("EngineCoreShader");
	EngineFile ShaderFile = ShaderDir.GetPlusFileName("BaseShader.hlsl");

	//Create Vertex Shader;
	std::shared_ptr<EngineVertexShader> Vs = EngineVertexShader::Load(ShaderFile, "vs_main");

	// Create Pixel Shader
	std::shared_ptr<EnginePixelShader> Ps = EnginePixelShader::Load(ShaderFile, "ps_main");
	
	// Create Input Layout
	EngineVertex::LayOutInfo.AddInputLayOut("POS", DXGI_FORMAT_R32G32B32A32_FLOAT);
	EngineVertex::LayOutInfo.AddInputLayOut("TEX", DXGI_FORMAT_R32G32B32A32_FLOAT);
	EngineVertex::LayOutInfo.AddInputLayOut("COL", DXGI_FORMAT_R32G32B32A32_FLOAT);
	
	const std::vector<D3D11_INPUT_ELEMENT_DESC>& LayOutInfos = EngineVertex::LayOutInfo.GetDescs();
	EngineInputLayout::Load("Pos4_Tex4_Col4", LayOutInfos.data(), static_cast<UINT>(LayOutInfos.size()), Vs);

	// Create Vertex Data
	std::vector<EngineVertex> VertexData(6);

	//�»�
	VertexData[0].POSITION = { -0.5f, 0.5f, 0.0f, 1.0f };
	VertexData[0].TEXCOORD = { 0.0f,  0.0f, 0.0f, 1.0f };
	VertexData[0].COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };

	//����
	VertexData[1].POSITION = { 0.5f, -0.5f, 0.0f, 1.0f };
	VertexData[1].TEXCOORD = { 0.0f,  1.0f, 0.0f, 1.0f };
	VertexData[1].COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };

	//����
	VertexData[2].POSITION = { -0.5f, -0.5f, 0.0f, 1.0f };
	VertexData[2].TEXCOORD = { 1.0f,  1.0f, 0.0f, 1.0f };
	VertexData[2].COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };

	//�»�
	VertexData[3].POSITION = { -0.5f,  0.5f, 0.0f, 1.0f };
	VertexData[3].TEXCOORD = { 0.0f,  0.0f, 0.0f, 1.0f };
	VertexData[3].COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };

	//���
	VertexData[4].POSITION = { 0.5f, 0.5f, 0.0f, 1.0f };
	VertexData[4].TEXCOORD = { 1.0f, 1.0f, 0.0f, 1.0f };
	VertexData[4].COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };

	//����
	VertexData[5].POSITION = { 0.5f, -0.5f, 0.0f, 1.0f };
	VertexData[5].TEXCOORD = { 1.0f,  0.0f, 0.0f, 1.0f };
	VertexData[5].COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	// Create Vertex Buffer
	EngineVertexBuffer::Load("Rect", VertexData);


}

void EngineDevice::CreateDepthStencil()
{
	float4 ScreenSize = EngineWindow::GetScreenSize();

	D3D11_TEXTURE2D_DESC DepthStencilDesc = { 0, };
	DepthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	DepthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthStencilDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	DepthStencilDesc.Width = static_cast<UINT>(ScreenSize.ix());
	DepthStencilDesc.Height = static_cast<UINT>(ScreenSize.iy());
	DepthStencilDesc.ArraySize = 1;
	DepthStencilDesc.SampleDesc.Count = 1;
	DepthStencilDesc.SampleDesc.Quality = 0;

	HRESULT Result = Device->CreateTexture2D(&DepthStencilDesc, nullptr, &DepthStencileBuffer);
	if (FAILED(Result))
	{
		MsgAssert("�������ٽǹ��� ������ �����߽��ϴ�.");
		return;
	}

	Result = Device->CreateDepthStencilView(DepthStencileBuffer, nullptr, &MainDSV);
	if (FAILED(Result))
	{
		MsgAssert("�������ٽǺ� ������ �����߽��ϴ�.");
		return;
	}
}

void EngineDevice::RenderStart()
{
	const static float4 clear_color = { 0.45f, 0.55f, 0.60f, 1.00f };
	EngineDevice::GetContext()->ClearRenderTargetView(EngineDevice::GetRTV(), clear_color.Arr1D);
	EngineDevice::GetContext()->OMSetRenderTargets(1, EngineDevice::GetRTVRef(), nullptr);
}

void EngineDevice::RenderEnd()
{
	HRESULT Result = SwapChain->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		// ����̽� �ٽø����
		MsgAssert("����Ÿ�� ������ �����߽��ϴ�.");
		return;
	}
}


void EngineDevice::Initialize()
{

	if (nullptr == EngineWindow::GethWnd())
	{
		MsgAssert("�����찡 ��������� �ʾҴµ� ����̽��� �ʰ�ȭ �Ҽ��� �����ϴ�.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// ���̷�Ʈx�� ����� ����� �����ϴµ�
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// �� ��ʹ� �׷���ī��� ���� ����Ǵ� �������̽�
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("�׷���ī�� ��ġ ��� �������̽��� �����µ� �����߽��ϴ�.");
		return;
	}

	ID3D11Device* BaseDevice;
	ID3D11DeviceContext* BaseContext;

	HRESULT Result = D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&BaseDevice,
		&Level,
		&BaseContext
	);

	if (S_OK != Result)
	{
		//MsgAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	Result = BaseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)&Device);
	assert(SUCCEEDED(Result));
	BaseDevice->Release();

	Result = BaseContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&Context);
	assert(SUCCEEDED(Result));
	BaseContext->Release();

	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		//MsgAssert("���̷�Ʈ 11�� �������� �ʴ� �׷���ī�� �Դϴ�");
		return;
	}

	// ��Ƽ������ ����ϰڴٴ� ������ �س���.
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (S_OK != Result)
	{
		//MsgAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	CreateSwapChain();
	CreateResorces();
	//CreateDepthStencil();
}

void EngineDevice::Release()
{
	//TestTriAngleResorece
	EngineVertexShader::ResorcesClear();
	EnginePixelShader::ResorcesClear();
	EngineInputLayout::ResorcesClear();
	EngineVertexBuffer::ResorcesClear();

	//RealLogic
	if (nullptr != BackBuffer)
	{
		BackBuffer->Release();
		BackBuffer = nullptr;
	}

	if (nullptr != DepthStencileBuffer)
	{
		DepthStencileBuffer->Release();
		DepthStencileBuffer = nullptr;
	}

	if (nullptr != MainDSV)
	{
		MainDSV->Release();
		MainDSV = nullptr;
	}

	if (nullptr != MainRTV)
	{
		MainRTV->Release();
		MainRTV = nullptr;
	}
	if (nullptr != SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}
}