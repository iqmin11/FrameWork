#pragma once
#include "EngineResource.h"
#include "ThirdParty/DirectXTex/inc/DirectXTex.h"
#include "EngineDirectX.h"

// Ό³Έν :
class EngineTexture : public EngineResource<EngineTexture>
{
	friend EngineDirectX;

public:
	// constrcuter destructer
	EngineTexture();
	~EngineTexture();

	// delete Function
	EngineTexture(const EngineTexture& _Other) = delete;
	EngineTexture(EngineTexture&& _Other) noexcept = delete;
	EngineTexture& operator=(const EngineTexture& _Other) = delete;
	EngineTexture& operator=(EngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<EngineTexture> Create(D3D11_TEXTURE2D_DESC _Desc)
	{
		std::shared_ptr<EngineTexture> NewTexture = EngineResource::CreateInst();
		NewTexture->ResCreate(_Desc);
		return NewTexture;
	}

	//Getter

	WRL::ComPtr<ID3D11ShaderResourceView> GetSRV()
	{
		return SRV;
	}

	WRL::ComPtr<ID3D11RenderTargetView> GetRTV()
	{
		return RTV;
	}

	WRL::ComPtr<ID3D11DepthStencilView> GetDSV()
	{
		return DSV;
	}

	unsigned int GetHeight()
	{
		return Desc.Height;
	}

	unsigned int GetWidth()
	{
		return Desc.Width;
	}

protected:

private:
	WRL::ComPtr<ID3D11Texture2D> Texture2D = nullptr;
	WRL::ComPtr<ID3D11ShaderResourceView> SRV = nullptr;
	WRL::ComPtr<ID3D11RenderTargetView> RTV = nullptr;
	WRL::ComPtr<ID3D11DepthStencilView> DSV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;
	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;
	
	void ResCreateForBackbuffer(WRL::ComPtr<ID3D11Texture2D> _Texture);
	void ResCreate(const D3D11_TEXTURE2D_DESC _Desc);

	void CreateSRV();
	void CreateRTV();
	void CreateDSV();
};

