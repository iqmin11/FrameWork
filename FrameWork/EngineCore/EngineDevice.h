#pragma once

// ���� :
class EngineDevice
{
public:
	// delete Function
	EngineDevice(const EngineDevice& _Other) = delete;
	EngineDevice(EngineDevice&& _Other) noexcept = delete;
	EngineDevice& operator=(const EngineDevice& _Other) = delete;
	EngineDevice& operator=(EngineDevice&& _Other) noexcept = delete;

	static void Initialize();

	static void CreateSwapChain();
	static void CreateResorces();
	static void CreateDepthStencil();

	static void Release();

	static void RenderStart();

	static void RenderEnd();

	inline static ID3D11Device* GetDevice()
	{
		return Device;
	}

	inline static ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

	inline static ID3D11RenderTargetView* GetRTV()
	{
		return MainRTV;
	}

	inline static ID3D11RenderTargetView** GetRTVRef()
	{
		return &MainRTV;
	}

	inline static ID3D11Texture2D* GetBackBuffer()
	{
		return BackBuffer;
	}

	static void Draw();

	// HWND
protected:

private:

	static ID3D11Device1* Device;
	static ID3D11DeviceContext1* Context;
	static IDXGISwapChain1* SwapChain;
	static IDXGIAdapter* GetHighPerformanceAdapter();
	
	static ID3D11Texture2D* BackBuffer;
	static ID3D11RenderTargetView* MainRTV;

	static ID3D11Texture2D* DepthStencileBuffer;
	static ID3D11DepthStencilView* MainDSV;

	// constrcuter destructer
	EngineDevice();
	~EngineDevice();
};

