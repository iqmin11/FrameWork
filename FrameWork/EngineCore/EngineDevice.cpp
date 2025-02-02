#include "PrecompileHeader.h"
#include "EngineDevice.h"

#include "EngineBase/EngineDirectory.h"
#include "EngineBase/EngineFile.h"

#include "EnginePlatform/EngineWindow.h"

#include "EngineResorce.h"
#include "EngineVertexShader.h"


ID3D11Device1* EngineDevice::Device = nullptr;
ID3D11DeviceContext1* EngineDevice::Context = nullptr;
IDXGISwapChain1* EngineDevice::SwapChain = nullptr;
ID3D11Texture2D* EngineDevice::BackBuffer = nullptr;
ID3D11RenderTargetView* EngineDevice::MainRTV = nullptr;
ID3D11Texture2D* EngineDevice::DepthStencileBuffer = nullptr;
ID3D11DepthStencilView* EngineDevice::MainDSV = nullptr;
ID3D11VertexShader* EngineDevice::VertexShader = nullptr;
ID3D11PixelShader* EngineDevice::PixelShader = nullptr;
ID3D11InputLayout* EngineDevice::InputLayout = nullptr;
ID3D11Buffer* EngineDevice::VertexBuffer = nullptr;
UINT EngineDevice::NumVerts;
UINT EngineDevice::Stride;
UINT EngineDevice::Offset;

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
	Context->IASetInputLayout(InputLayout);

	Context->VSSetShader(VertexShader, nullptr, 0);
	Context->PSSetShader(PixelShader, nullptr, 0);

	Context->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);

	Context->Draw(NumVerts, 0);

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
	ID3DBlob* VsBlob;
	{
		ID3DBlob* ShaderCompileErrorsBlob;
		HRESULT Result = D3DCompileFromFile(ShaderFile.GetFullPathToWstring().c_str(), nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &VsBlob, &ShaderCompileErrorsBlob);

		if (FAILED(Result))
		{
			const char* errorString = NULL;
			if (Result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			{
				errorString = "Could not compile shader; file not found";
			}
			else if (ShaderCompileErrorsBlob) 
			{
				errorString = (const char*)ShaderCompileErrorsBlob->GetBufferPointer();
				ShaderCompileErrorsBlob->Release();
			}
			MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
			return;
		}

		Result = Device->CreateVertexShader(VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(), nullptr, &VertexShader);
		assert(SUCCEEDED(Result));
	}

	// Create Pixel Shader
	{
		ID3DBlob* PsBlob;
		ID3DBlob* ShaderCompileErrorsBlob;
		HRESULT hResult = D3DCompileFromFile(ShaderFile.GetFullPathToWstring().c_str(), nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &PsBlob, &ShaderCompileErrorsBlob);
		if (FAILED(hResult))
		{
			const char* errorString = NULL;
			if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			{
				errorString = "Could not compile shader; file not found";
			}
			else if (ShaderCompileErrorsBlob)
			{
				errorString = (const char*)ShaderCompileErrorsBlob->GetBufferPointer();
				ShaderCompileErrorsBlob->Release();
			}
			MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
			return;
		}

		hResult = Device->CreatePixelShader(PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(), nullptr, &PixelShader);
		assert(SUCCEEDED(hResult));
		PsBlob->Release();
	}

	// Create Input Layout
	{
		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{ "POS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		HRESULT hResult = Device->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc), VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(), &InputLayout);
		assert(SUCCEEDED(hResult));
		VsBlob->Release();
	}

	// Create Vertex Buffer
	{
		float VertexData[] = 
		{ // x, y, r, g, b, a
			0.0f,  0.5f, 0.f, 1.f, 0.f, 1.f,
			0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f,
			-0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f
		};
		Stride = 6 * sizeof(float);
		NumVerts = sizeof(VertexData) / Stride;
		Offset = 0;

		D3D11_BUFFER_DESC VertexBufferDesc = {};
		VertexBufferDesc.ByteWidth = sizeof(VertexData);
		VertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA VertexSubresourceData = { VertexData };

		HRESULT hResult = Device->CreateBuffer(&VertexBufferDesc, &VertexSubresourceData, &VertexBuffer);
		assert(SUCCEEDED(hResult));
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
	if (nullptr != VertexShader)
	{
		VertexShader->Release();
		VertexShader = nullptr;
	}

	if (nullptr != PixelShader)
	{
		PixelShader->Release();
		PixelShader = nullptr;
	}

	if (nullptr != InputLayout)
	{
		InputLayout->Release();
		InputLayout = nullptr;
	}

	if (nullptr != VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}

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