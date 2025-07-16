#include "PrecompileHeader.h"
#include "EngineDevice.h"

#include "EngineBase/EngineDirectory.h"
#include "EngineBase/EngineFile.h"

#include "EnginePlatform/EngineWindow.h"

EngineDevice::EngineDevice()
{
}

EngineDevice::~EngineDevice()
{
}

void EngineDevice::Draw()
{
	
}

WRL::ComPtr<IDXGIAdapter> EngineDevice::GetHighPerformanceAdapter()
{
	// GDI+ DXGI <=

	WRL::ComPtr<IDXGIFactory> Factory = nullptr;
	WRL::ComPtr<IDXGIAdapter> Adapter = nullptr;

	// c++���� �����ϴ� Ŭ������ �����ϱ� ���� GUI�� ������ 
	// 
	// MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)Factory.GetAddressOf());

	if (nullptr == Factory)
	{
		MsgAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
		return nullptr;
	}

	size_t prevAdapterVideoMemory = 0;

	for (UINT Adapterindex = 0; ; Adapterindex++)
	{
		WRL::ComPtr<IDXGIAdapter> CurAdapter = nullptr;

		Factory->EnumAdapters(Adapterindex, CurAdapter.GetAddressOf());
		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (prevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			prevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			Adapter = CurAdapter;
			continue;
		}
	}

	return Adapter;
}

void EngineDevice::CreateSwapChain()
{
	//SwapChain ��ü ���� Process
	{
		//Dxgi���丮 ��ü ����
		WRL::ComPtr<IDXGIFactory2> DxgiFactory;
		{
			//���丮�� ������ ���� ���� ����
			//1. Device�� ����dxgiDevice�� �������
			//2. dxgiDevice�� ���� dxgiAdapter�� �������
			//3. DxgiAdapter�� ���� Factory�� ������ ��

			//DxgiDevice ��ü�� Device�� ���� �޾ƿ�.
			WRL::ComPtr<IDXGIDevice1> DxgiDevice;
			HRESULT Result = Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)DxgiDevice.GetAddressOf());
			assert(SUCCEEDED(Result));

			//DxgiDevice�� ���� DxgiAdapter�� �޾ƿ�
			WRL::ComPtr<IDXGIAdapter> DxgiAdapter;
			Result = DxgiDevice->GetAdapter(&DxgiAdapter);
			assert(SUCCEEDED(Result));

			//DxgiAdapter�� ���� AdapterDesc�� �޾ƿ�
			DXGI_ADAPTER_DESC AdapterDesc;
			DxgiAdapter->GetDesc(&AdapterDesc);

			//���� � �׷��� ����̽�(�׷���ī��)�� ����ϴ��� �����
			OutputDebugStringA("Graphics Device: ");
			OutputDebugStringW(AdapterDesc.Description);

			//�ش� ������� ���丮�� �������(�θ�)
			Result = DxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)DxgiFactory.GetAddressOf());
			assert(SUCCEEDED(Result));
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
		HRESULT Result = DxgiFactory->CreateSwapChainForHwnd(Device.Get(), EngineWindow::GethWnd(), &SwapChainDesc, 0, 0, &SwapChain);
		assert(SUCCEEDED(Result));
	}
	
	//Swapchain�� FrameBuffer ����
	{
		//FrameBuffer �޾ƿ���
		WRL::ComPtr<ID3D11Texture2D> BackBuffer = nullptr;

		HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		assert(SUCCEEDED(Result));

		Result = Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, &MainRTV);
		assert(SUCCEEDED(Result));
	}
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

	Result = Device->CreateDepthStencilView(DepthStencileBuffer.Get(), nullptr, &MainDSV);
	if (FAILED(Result))
	{
		MsgAssert("�������ٽǺ� ������ �����߽��ϴ�.");
		return;
	}
}

void EngineDevice::RenderStart()
{
	const static float4 clear_color = { 0.45f, 0.55f, 0.60f, 1.00f };
	Context->ClearRenderTargetView(EngineDevice::GetRTV().Get(), clear_color.Arr1D);
}

void EngineDevice::RenderEnd()
{
	HRESULT Result = SwapChain->Present(1, 0);
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
	WRL::ComPtr<IDXGIAdapter> Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("�׷���ī�� ��ġ ��� �������̽��� �����µ� �����߽��ϴ�.");
		return;
	}

	WRL::ComPtr<ID3D11Device> BaseDevice;
	WRL::ComPtr<ID3D11DeviceContext> BaseContext;

	HRESULT Result = D3D11CreateDevice(
		Adapter.Get(),
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		BaseDevice.GetAddressOf(),
		&Level,
		BaseContext.GetAddressOf()
	);

	if (S_OK != Result)
	{
		//MsgAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	Result = BaseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)Device.GetAddressOf());
	assert(SUCCEEDED(Result));

	Result = BaseContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)Context.GetAddressOf());
	assert(SUCCEEDED(Result));

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
	//CreateDepthStencil();
}

void EngineDevice::Release()
{
}