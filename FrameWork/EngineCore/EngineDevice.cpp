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

	// c++에서 지원하는 클래스를 구분하기 위한 GUI를 얻어오는 
	// 
	// MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)Factory.GetAddressOf());

	if (nullptr == Factory)
	{
		MsgAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
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
	//SwapChain 개체 세팅 Process
	{
		//Dxgi팩토리 개체 생성
		WRL::ComPtr<IDXGIFactory2> DxgiFactory;
		{
			//팩토리를 가지고 오기 위한 과정
			//1. Device로 부터dxgiDevice를 가지고옴
			//2. dxgiDevice로 부터 dxgiAdapter를 가지고옴
			//3. DxgiAdapter로 부터 Factory를 가지고 옴

			//DxgiDevice 개체를 Device로 부터 받아옴.
			WRL::ComPtr<IDXGIDevice1> DxgiDevice;
			HRESULT Result = Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)DxgiDevice.GetAddressOf());
			assert(SUCCEEDED(Result));

			//DxgiDevice를 통해 DxgiAdapter를 받아옴
			WRL::ComPtr<IDXGIAdapter> DxgiAdapter;
			Result = DxgiDevice->GetAdapter(&DxgiAdapter);
			assert(SUCCEEDED(Result));

			//DxgiAdapter를 통해 AdapterDesc를 받아옴
			DXGI_ADAPTER_DESC AdapterDesc;
			DxgiAdapter->GetDesc(&AdapterDesc);

			//내가 어떤 그래픽 디바이스(그래픽카드)를 사용하는지 출력함
			OutputDebugStringA("Graphics Device: ");
			OutputDebugStringW(AdapterDesc.Description);

			//해당 어댑터의 팩토리를 가지고옴(부모)
			Result = DxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)DxgiFactory.GetAddressOf());
			assert(SUCCEEDED(Result));
		}

		//Swapchain을 위한 Desc를 설정하고
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

		//Factory를 통해, Swapchain을 생성
		HRESULT Result = DxgiFactory->CreateSwapChainForHwnd(Device.Get(), EngineWindow::GethWnd(), &SwapChainDesc, 0, 0, &SwapChain);
		assert(SUCCEEDED(Result));
	}
	
	//Swapchain에 FrameBuffer 세팅
	{
		//FrameBuffer 받아오기
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
		MsgAssert("뎁스스텐실버퍼 생성에 실패했습니다.");
		return;
	}

	Result = Device->CreateDepthStencilView(DepthStencileBuffer.Get(), nullptr, &MainDSV);
	if (FAILED(Result))
	{
		MsgAssert("뎁스스텐실뷰 생성에 실패했습니다.");
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
		// 디바이스 다시만들기
		MsgAssert("랜더타겟 생성에 실패했습니다.");
		return;
	}
}

void EngineDevice::Initialize()
{

	if (nullptr == EngineWindow::GethWnd())
	{
		MsgAssert("윈도우가 만들어지지 않았는데 디바이스를 초가화 할수는 없습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// 다이렉트x도 디버그 기능을 지원하는데
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// 이 어뎁터는 그래픽카드와 직접 연결되는 인터페이스
	WRL::ComPtr<IDXGIAdapter> Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("그래픽카드 장치 어뎁터 인터페이스를 얻어오는데 실패했습니다.");
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
		//MsgAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	Result = BaseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)Device.GetAddressOf());
	assert(SUCCEEDED(Result));

	Result = BaseContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)Context.GetAddressOf());
	assert(SUCCEEDED(Result));

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		//MsgAssert("다이렉트 11을 지원하지 않는 그래픽카드 입니다");
		return;
	}

	// 멀티쓰레드 사용하겠다는 설정을 해놨다.
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (S_OK != Result)
	{
		//MsgAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	CreateSwapChain();
	//CreateDepthStencil();
}

void EngineDevice::Release()
{
}