#pragma once
#include <d3d11.h>

// Ό³Έν :
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

	// HWND
protected:

private:

	static ID3D11Device* Device;
	static ID3D11DeviceContext* Context;
	static IDXGISwapChain* SwapChain;
	static IDXGIAdapter* GetHighPerformanceAdapter();
	static ID3D11Texture2D* BackBuffer;
	static ID3D11RenderTargetView* MainRTV;

	// constrcuter destructer
	EngineDevice();
	~EngineDevice();
};

