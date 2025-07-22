#include "PrecompileHeader.h"
#include "EngineViewportTarget.h"

#include "EngineTexture.h"

EngineViewportTarget::EngineViewportTarget() 
{
}

EngineViewportTarget::~EngineViewportTarget() 
{
}

void EngineViewportTarget::CreateDepthTexture(int _Index)
{
	D3D11_TEXTURE2D_DESC Desc {};

	Desc.ArraySize = 1;
	Desc.Width = Textures[_Index]->GetWidth();
	Desc.Height = Textures[_Index]->GetHeight();
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.MipLevels = 1;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.CPUAccessFlags = 0;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	DepthTexture = EngineTexture::Create(Desc);
}

void EngineViewportTarget::ResCreate(std::shared_ptr<EngineTexture> _Texture, float4 _Color)
{
	Textures.emplace_back(_Texture);
	SRVs.emplace_back(_Texture->GetSRV());
	RTVs.emplace_back(_Texture->GetRTV());
	Color.push_back(_Color);

	D3D11_VIEWPORT ViewportData;

	ViewportData.TopLeftX = 0;
	ViewportData.TopLeftY = 0;
	ViewportData.Width = static_cast<float>(_Texture->GetHeight());
	ViewportData.Height = static_cast<float>(_Texture->GetWidth());
	ViewportData.MinDepth = 0.0f;
	ViewportData.MaxDepth = 1.0f;

	ViewportDatas.emplace_back(ViewportData);
}

void EngineViewportTarget::Clear()
{
	for (size_t i = 0; i < Textures.size(); i++)
	{
		WRL::ComPtr<ID3D11RenderTargetView> RTV = Textures[i]->GetRTV();

		if (RTV == nullptr)
		{
			MsgAssert("랜더타겟 뷰가 존재하지 않아 클리어 불가능");
			return;
		}

		EngineDirectX::GetContext()->ClearRenderTargetView(RTV.Get(), Color[i].Arr1D);
	}

	if (DepthTexture == nullptr)
	{
		return;
	}

	EngineDirectX::GetContext()->ClearDepthStencilView(DepthTexture->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void EngineViewportTarget::Setting()
{
	ID3D11RenderTargetView** RTV = RTVs[0].GetAddressOf();

	if (RTV == nullptr)
	{
		MsgAssert("랜더타겟 뷰가 존재하지 않아서 클리어가 불가능합니다.");
	}

	ID3D11DepthStencilView* DSV = DepthTexture != nullptr ? DepthTexture->GetDSV().Get() : nullptr;

	EngineDirectX::GetContext()->OMSetRenderTargets(static_cast<UINT>(RTVs.size()), RTV, DSV);
	EngineDirectX::GetContext()->RSSetViewports(static_cast<unsigned int>(ViewportDatas.size()), &ViewportDatas[0]);
}


