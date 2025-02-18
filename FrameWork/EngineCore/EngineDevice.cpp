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
	//SwapChain 개체 세팅 Process
	{
		//Dxgi팩토리 개체 생성
		IDXGIFactory2* DxgiFactory;
		{
			//팩토리를 가지고 오기 위한 과정
			//1. Device로 부터dxgiDevice를 가지고옴
			//2. dxgiDevice로 부터 dxgiAdapter를 가지고옴
			//3. DxgiAdapter로 부터 Factory를 가지고 옴

			//DxgiDevice 개체를 Device로 부터 받아옴.
			IDXGIDevice1* DxgiDevice;
			HRESULT Result = Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&DxgiDevice);
			assert(SUCCEEDED(Result));

			//DxgiDevice를 통해 DxgiAdapter를 받아옴
			IDXGIAdapter* DxgiAdapter;
			Result = DxgiDevice->GetAdapter(&DxgiAdapter);
			assert(SUCCEEDED(Result));
			DxgiDevice->Release();

			//DxgiAdapter를 통해 AdapterDesc를 받아옴
			DXGI_ADAPTER_DESC AdapterDesc;
			DxgiAdapter->GetDesc(&AdapterDesc);

			//내가 어떤 그래픽 디바이스(그래픽카드)를 사용하는지 출력함
			OutputDebugStringA("Graphics Device: ");
			OutputDebugStringW(AdapterDesc.Description);

			//해당 어댑터의 팩토리를 가지고옴(부모)
			Result = DxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&DxgiFactory);
			assert(SUCCEEDED(Result));

			//어댑터 릴리즈
			DxgiAdapter->Release();
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
		HRESULT Result = DxgiFactory->CreateSwapChainForHwnd(Device, EngineWindow::GethWnd(), &SwapChainDesc, 0, 0, &SwapChain);
		assert(SUCCEEDED(Result));

		//Swapchain을 만드는데 성공하면 Factory를 Release;
		DxgiFactory->Release();
	}
	
	//Swapchain에 FrameBuffer 세팅
	{
		//FrameBuffer 받아오기
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

	//좌상
	VertexData[0].POSITION = { -0.5f, 0.5f, 0.0f, 1.0f };
	VertexData[0].TEXCOORD = { 0.0f,  0.0f, 0.0f, 1.0f };
	VertexData[0].COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };

	//우하
	VertexData[1].POSITION = { 0.5f, -0.5f, 0.0f, 1.0f };
	VertexData[1].TEXCOORD = { 0.0f,  1.0f, 0.0f, 1.0f };
	VertexData[1].COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };

	//좌하
	VertexData[2].POSITION = { -0.5f, -0.5f, 0.0f, 1.0f };
	VertexData[2].TEXCOORD = { 1.0f,  1.0f, 0.0f, 1.0f };
	VertexData[2].COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };

	//좌상
	VertexData[3].POSITION = { -0.5f,  0.5f, 0.0f, 1.0f };
	VertexData[3].TEXCOORD = { 0.0f,  0.0f, 0.0f, 1.0f };
	VertexData[3].COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };

	//우상
	VertexData[4].POSITION = { 0.5f, 0.5f, 0.0f, 1.0f };
	VertexData[4].TEXCOORD = { 1.0f, 1.0f, 0.0f, 1.0f };
	VertexData[4].COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };

	//우하
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
		MsgAssert("뎁스스텐실버퍼 생성에 실패했습니다.");
		return;
	}

	Result = Device->CreateDepthStencilView(DepthStencileBuffer, nullptr, &MainDSV);
	if (FAILED(Result))
	{
		MsgAssert("뎁스스텐실뷰 생성에 실패했습니다.");
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
		//MsgAssert("디바이스 생성에 실패했습니다.");
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