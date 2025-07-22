#include "PrecompileHeader.h"
#include "EngineTexture.h"

#include "EngineDirectX.h"

#ifdef _DEBUG
#pragma comment(lib, "C:\\Dev\\FrameWork\\FrameWork\\ThirdParty\\DirectXTex\\bin\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "C:\\Dev\\FrameWork\\FrameWork\\ThirdParty\\DirectXTex\\bin\\Release\\DirectXTex.lib")
#endif // _DEBUG

EngineTexture::EngineTexture() 
{
}

EngineTexture::~EngineTexture() 
{
	Image.Release();
}

void EngineTexture::ResCreateForBackbuffer(WRL::ComPtr<ID3D11Texture2D> _Texture)
{
	Texture2D = _Texture;
	Texture2D->GetDesc(&Desc);

	CreateRTV();
}

void EngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC _Desc)
{
	Desc = _Desc;

	HRESULT Result = EngineDirectX::GetDevice()->CreateTexture2D(&Desc, nullptr, Texture2D.GetAddressOf());

	if (Result != S_OK)
	{
		MsgAssert("�ؽ�ó ������ �����߽��ϴ�.");
	}

	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
	{
		CreateSRV();
	}

	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
	{
		CreateRTV();
	}

	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
	{
		CreateDSV();
	}
}

void EngineTexture::CreateRTV()
{
	if (Texture2D == nullptr)
	{
		MsgAssert("�ؽ��İ� �������� �ʽ��ϴ�.");
		return;
	}

	HRESULT Result = EngineDirectX::GetDevice()->CreateRenderTargetView(Texture2D.Get(), nullptr, RTV.GetAddressOf());

	if (Result != S_OK)
	{
		MsgAssert("����Ÿ�� �� ������ �����߽��ϴ�.");
		return;
	}
}

void EngineTexture::CreateDSV()
{
	if (Texture2D == nullptr)
	{
		MsgAssert("�ؽ��İ� �������� �ʽ��ϴ�.");
		return;
	}

	HRESULT Result = EngineDirectX::GetDevice()->CreateDepthStencilView(Texture2D.Get(), nullptr, DSV.GetAddressOf());

	if (Result != S_OK)
	{
		MsgAssert("���� ���Ľ� �� ������ �����߽��ϴ�.");
		return;
	}
}

void EngineTexture::CreateSRV()
{
	if (Texture2D == nullptr)
	{
		MsgAssert("�ؽ��İ� �������� �ʽ��ϴ�.");
		return;
	}

	HRESULT Result = EngineDirectX::GetDevice()->CreateShaderResourceView(Texture2D.Get(), nullptr, SRV.GetAddressOf());

	if (Result != S_OK)
	{
		MsgAssert("���� ���Ľ� �� ������ �����߽��ϴ�.");
		return;
	}
}

//void EngineTexture::ResCreate(ID3D11Texture2D* _Texture)
//{
//	Texture2D = _Texture;
//	Texture2D->GetDesc(&Desc);
//
//
//}

