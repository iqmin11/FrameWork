#include "PrecompileHeader.h"
#include "EngineDirectX.h"

#include "EngineBase/EngineDirectory.h"
#include "EngineBase/EngineFile.h"

#include "EnginePlatform/EngineWindow.h"

#include "EngineTexture.h"
#include "EngineViewportTarget.h"

EngineDirectX::EngineDirectX()
{
}

EngineDirectX::~EngineDirectX()
{
}

void EngineDirectX::Draw()
{
}

WRL::ComPtr<IDXGIAdapter> EngineDirectX::GetHighPerformanceAdapter()
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

void EngineDirectX::CreateSwapChain()
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
		float4 ScreenSize = EngineWindow::GetScreenSize();

		DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0, };

		SwapChainDesc.BufferCount = 2;
		SwapChainDesc.BufferDesc.Width = ScreenSize.uix();
		SwapChainDesc.BufferDesc.Height = ScreenSize.uiy();
		SwapChainDesc.OutputWindow = EngineWindow::GethWnd();

		SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;

		SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

		SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.SampleDesc.Count = 1;

		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		SwapChainDesc.Windowed = true;

		//Factory�� ����, Swapchain�� ����
		HRESULT Result = DxgiFactory->CreateSwapChain(Device.Get(), &SwapChainDesc, SwapChain.GetAddressOf());
		assert(SUCCEEDED(Result));
	}

	//Swapchain�� FrameBuffer ����
	{
		//FrameBuffer �޾ƿ���

		WRL::ComPtr<ID3D11Texture2D> SwapChainOutBackBuffer = nullptr;
		HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)SwapChainOutBackBuffer.GetAddressOf());
		assert(SUCCEEDED(Result));

		std::shared_ptr<EngineTexture> EngineBackBuffer = std::make_shared<EngineTexture>();
		EngineBackBuffer->ResCreateForBackbuffer(SwapChainOutBackBuffer);
		assert(SUCCEEDED(Result));

		BackBufferTarget = EngineViewportTarget::Create("MainBackBufferTarget", EngineBackBuffer, float4::BLUE);
		BackBufferTarget->CreateDepthTexture();
	}
}

void EngineDirectX::DrawStart()
{
	BackBufferTarget->Clear();
	BackBufferTarget->Setting();
}

void EngineDirectX::DrawEnd()
{
	HRESULT Result = SwapChain->Present(1, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		// ����̽� �ٽø����
		MsgAssert("����Ÿ�� ������ �����߽��ϴ�.");
		return;
	}
}

void EngineDirectX::Initialize()
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

void EngineDirectX::Release()
{

}