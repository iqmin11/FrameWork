#pragma once

// Ό³Έν :

class EngineViewportTarget;
class EngineDirectX
{
public:
	// delete Function
	EngineDirectX(const EngineDirectX& _Other) = delete;
	EngineDirectX(EngineDirectX&& _Other) noexcept = delete;
	EngineDirectX& operator=(const EngineDirectX& _Other) = delete;
	EngineDirectX& operator=(EngineDirectX&& _Other) noexcept = delete;

	// Initialize
	static void Initialize();
	static void CreateSwapChain();

	// Rendering
	static void DrawStart();
	static void Draw();
	static void DrawEnd();

	// Release
	static void Release();

	// Getters
	inline static WRL::ComPtr<ID3D11Device> GetDevice()
	{
		return Device;
	}

	inline static WRL::ComPtr<ID3D11DeviceContext> GetContext()
	{
		return Context;
	}

protected:

private:

	inline static WRL::ComPtr<ID3D11Device1> Device = nullptr;
	inline static WRL::ComPtr<ID3D11DeviceContext> Context = nullptr;
	inline static WRL::ComPtr<IDXGISwapChain> SwapChain = nullptr;
	static WRL::ComPtr<IDXGIAdapter> GetHighPerformanceAdapter();

	inline static std::shared_ptr<EngineViewportTarget> BackBufferTarget = nullptr;

	// constrcuter destructer
	EngineDirectX();
	~EngineDirectX();
};

