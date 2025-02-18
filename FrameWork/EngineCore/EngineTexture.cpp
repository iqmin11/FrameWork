#include "PrecompileHeader.h"
#include "EngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Bin\\x64\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\Bin\\x64\\Release\\DirectXTex.lib")
#endif

EngineTexture::EngineTexture() 
{
}

EngineTexture::~EngineTexture() 
{
	Image.Release();

	if (Texture2D != nullptr)
	{
		Texture2D->Release();
	}

	if (SRV != nullptr)
	{
		SRV->Release();
	}
}

std::shared_ptr<EngineTexture> EngineTexture::Load(const EnginePath& Path, std::string_view TextureName)
{
	std::shared_ptr<EngineTexture> NewTexture = Create(TextureName);
	NewTexture->SetPath(Path);
	NewTexture->ResLoad(Path);

	return NewTexture;
}

void EngineTexture::ResLoad(const EnginePath& Path)
{
	std::string Ext = EngineString::ToUpper(Path.GetExtension());

	std::wstring WPath = Path.GetFullPathToWstring();

	HRESULT Result;
	if (Ext == ".TGA")
	{
		Result = DirectX::LoadFromTGAFile(WPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image);
	}
	else if (Ext == ".DDS")
	{
		Result = DirectX::LoadFromDDSFile(WPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image);
	}
	else
	{
		Result = DirectX::LoadFromWICFile(WPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image);
	}
	assert(SUCCEEDED(Result));

	Result = DirectX::CreateShaderResourceView(EngineDevice::GetDevice(), Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &SRV);
	assert(SUCCEEDED(Result));

	TextureDesc.Width = static_cast<UINT>(Data.width);
	TextureDesc.Height = static_cast<UINT>(Data.height);
}

