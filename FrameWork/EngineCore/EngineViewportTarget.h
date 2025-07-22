#pragma once
#include "EngineResource.h"

// Ό³Έν :
class EngineTexture;
class EngineViewportTarget : public EngineResource<EngineViewportTarget>
{
public:
	// constrcuter destructer
	EngineViewportTarget();
	~EngineViewportTarget();

	// delete Function
	EngineViewportTarget(const EngineViewportTarget& _Other) = delete;
	EngineViewportTarget(EngineViewportTarget&& _Other) noexcept = delete;
	EngineViewportTarget& operator=(const EngineViewportTarget& _Other) = delete;
	EngineViewportTarget& operator=(EngineViewportTarget&& _Other) noexcept = delete;

	static std::shared_ptr<EngineViewportTarget> Create(std::string_view _Name, std::shared_ptr<EngineTexture> _Texture, float4 _Color)
	{
		std::shared_ptr<EngineViewportTarget> NewViewportTarget = EngineResource::CreateInst(_Name);
		NewViewportTarget->ResCreate(_Texture, _Color);
		return NewViewportTarget;
	}

	void CreateDepthTexture(int _Index = 0);

	void Clear();
	void Setting() override;

protected:

private:
	std::vector<float4> Color;

	std::vector<std::shared_ptr<EngineTexture>> Textures;
	std::vector<D3D11_VIEWPORT> ViewportDatas;
	std::vector<WRL::ComPtr<ID3D11RenderTargetView>> RTVs;
	std::vector<WRL::ComPtr<ID3D11ShaderResourceView>> SRVs;

	std::shared_ptr<EngineTexture> DepthTexture = nullptr;

	void ResCreate(std::shared_ptr<EngineTexture> _Texture, float4 _Color);
};

