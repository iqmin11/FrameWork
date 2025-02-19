#pragma once
#include "EngineResorce.h"
#include <EngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>



// Ό³Έν :
class EngineTexture : public EngineResorce<EngineTexture>
{
public:
	// constrcuter destructer
	EngineTexture();
	~EngineTexture();

	// delete Function
	EngineTexture(const EngineTexture& _Other) = delete;
	EngineTexture(EngineTexture&& _Other) noexcept = delete;
	EngineTexture& operator=(const EngineTexture& _Other) = delete;
	EngineTexture& operator=(EngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<EngineTexture> Load(const EnginePath& Path, std::string_view TextureName);
	inline ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}

protected:

private:

	ID3D11Texture2D* Texture2D = nullptr;
	ID3D11ShaderResourceView* SRV = nullptr;
	
	DirectX::TexMetadata MetaData = {};
	DirectX::ScratchImage Image = {};

	D3D11_TEXTURE2D_DESC TextureDesc = {};

	void ResLoad(const EnginePath& Path);
};

