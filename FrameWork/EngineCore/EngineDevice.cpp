#include "PrecompileHeader.h"
#include "EngineDevice.h"
#include <EnginePlatform/EngineWindow.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")


ID3D11Device* EngineDevice::Device = nullptr;
ID3D11DeviceContext* EngineDevice::Context = nullptr;
IDXGISwapChain* EngineDevice::SwapChain = nullptr;
ID3D11Texture2D* EngineDevice::BackBuffer = nullptr;
ID3D11RenderTargetView* EngineDevice::MainRTV = nullptr;

EngineDevice::EngineDevice()
{
}

EngineDevice::~EngineDevice()
{
}

IDXGIAdapter* EngineDevice::GetHighPerformanceAdapter()
{
	// GDI+ DXGI <=

	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// c++에서 지원하는 클래스를 구분하기 위한 GUI를 얻어오는 
	// 
	// MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
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
	float4 ScreenSize = EngineWindow::GetScreenSize();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0, };

	// 기본정보
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.BufferDesc.Width = static_cast<UINT>(ScreenSize.ix());
	SwapChainDesc.BufferDesc.Height = static_cast<UINT>(ScreenSize.iy());
	SwapChainDesc.OutputWindow = EngineWindow::GethWnd();

	// 화면 갱신률
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;

	// 그래픽이미지 포맷
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	// 안티얼라이언싱 퀄리티 1짜리롤 
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// false면 전체화면
	SwapChainDesc.Windowed = true;

	IDXGIDevice* SwapDevice = nullptr;
	IDXGIAdapter* SwapAdapter = nullptr;
	IDXGIFactory* SwapFactory = nullptr;

	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&SwapDevice));
	if (nullptr == SwapDevice)
	{
		MsgAssert("DXGI 디바이스를 DirectX디바이스에서 얻어오지 못했습니다.");
		return;
	}

	SwapDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&SwapAdapter));
	if (nullptr == SwapAdapter)
	{
		MsgAssert("DXGI 디바이스를 DirectX디바이스에서 얻어오지 못했습니다.");
		return;
	}

	SwapAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&SwapFactory));

	if (S_OK != SwapFactory->CreateSwapChain(Device, &SwapChainDesc, &SwapChain))
	{
		MsgAssert("스왑체인 생성에 실패했습니다.");
		return;
	}

	SwapDevice->Release();
	SwapAdapter->Release();
	SwapFactory->Release();

	// 랜더타겟은 DC의 라고 보시면 됩니다.


	HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));
	if (S_OK != Result)
	{
		MsgAssert("스왑체인 생성에 실패했습니다.");
		return;
	}

	Device->CreateRenderTargetView(BackBuffer, nullptr, &MainRTV);
	BackBuffer->Release();
	BackBuffer = nullptr;
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
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("그래픽카드 장치 어뎁터 인터페이스를 얻어오는데 실패했습니다.");
		return;
	}

	HRESULT Result = D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&Context
	);

	if (S_OK != Result)
	{
		//MsgAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		//MsgAssert("다이렉트 11을 지원하지 않는 그래픽카드 입니다");
		return;
	}

	// 멀티쓰레드 사용하겠다는 설정을 해놨다.
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	CreateSwapChain();
}

void EngineDevice::Release()
{
	if (nullptr != BackBuffer)
	{
		BackBuffer->Release();
		BackBuffer = nullptr;
	}
	//BackBufferTarget = nullptr;
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