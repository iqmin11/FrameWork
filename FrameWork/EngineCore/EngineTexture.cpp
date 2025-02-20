#include "PrecompileHeader.h"
#include "EngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Bin\\x64\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\Bin\\x64\\Release\\DirectXTex.lib")
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <EngineCore/ThirdParty/stb/stb_image.h>

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

	//DirectXTex 라이브러리를 활용하여, ScratchImage 로드
	HRESULT Result;
	Result = DirectX::LoadFromWICFile(WPath.c_str(), DirectX::WIC_FLAGS_DEFAULT_SRGB, &MetaData, Image);
	assert(SUCCEEDED(Result));

	//ScratchImage로 SRV 생성
	Result = DirectX::CreateShaderResourceView(EngineDevice::GetDevice(), Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &SRV);
	assert(SUCCEEDED(Result));

	//Texture2D를 활용한 SRV생성 방법
	//TextureDesc.Width = static_cast<UINT>(MetaData.width);
	//TextureDesc.Height = static_cast<UINT>(MetaData.height);
	//TextureDesc.MipLevels = MetaData.mipLevels;
	//TextureDesc.ArraySize = MetaData.arraySize;
	//TextureDesc.Format = MetaData.format;
	//TextureDesc.SampleDesc.Count = 1;
	//TextureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	//TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	//// Create Texture
	//std::vector<D3D11_SUBRESOURCE_DATA> textureSubresourceData(MetaData.format);
	//const DirectX::Image* images = Image.GetImages();

	//for (size_t i = 0; i < textureSubresourceData.size(); i++)
	//{
	//	textureSubresourceData[i].pSysMem = images[i].pixels;
	//	textureSubresourceData[i].SysMemPitch = static_cast<UINT>(images[i].rowPitch);
	//	textureSubresourceData[i].SysMemSlicePitch = static_cast<UINT>(images[i].slicePitch);
	//}

	//EngineDevice::GetDevice()->CreateTexture2D(&TextureDesc, textureSubresourceData.data(), &Texture2D);

	//EngineDevice::GetDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

}

