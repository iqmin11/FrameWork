#pragma once

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
	static void CreateDepthStencil();

	static void Release();

	static void RenderStart();

	static void RenderEnd();

	inline static WRL::ComPtr<ID3D11Device> GetDevice()
	{
		return Device;
	}

	inline static WRL::ComPtr<ID3D11DeviceContext> GetContext()
	{
		return Context;
	}

	inline static WRL::ComPtr<ID3D11RenderTargetView> GetRTV()
	{
		return MainRTV;
	}

	inline static ID3D11RenderTargetView** GetRTVRef()
	{
		return MainRTV.GetAddressOf();
	}

	static void Draw();

	// HWND
protected:

private:

	inline static WRL::ComPtr<ID3D11Device1> Device = nullptr;
	inline static WRL::ComPtr<ID3D11DeviceContext1> Context = nullptr;
	inline static WRL::ComPtr<IDXGISwapChain1> SwapChain = nullptr;
	static WRL::ComPtr<IDXGIAdapter> GetHighPerformanceAdapter();
	
	inline static WRL::ComPtr<ID3D11RenderTargetView> MainRTV = nullptr;

	inline static WRL::ComPtr<ID3D11Texture2D> DepthStencileBuffer = nullptr;
	inline static WRL::ComPtr<ID3D11DepthStencilView> MainDSV = nullptr;

	// constrcuter destructer
	EngineDevice();
	~EngineDevice();
};

