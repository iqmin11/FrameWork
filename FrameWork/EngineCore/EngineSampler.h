#pragma once
#include "EngineResorce.h"

// Ό³Έν :
class EngineSampler : public EngineResorce<EngineSampler>
{
public:
	// constrcuter destructer
	EngineSampler();
	~EngineSampler();

	// delete Function
	EngineSampler(const EngineSampler& _Other) = delete;
	EngineSampler(EngineSampler&& _Other) noexcept = delete;
	EngineSampler& operator=(const EngineSampler& _Other) = delete;
	EngineSampler& operator=(EngineSampler&& _Other) noexcept = delete;
	
	static std::shared_ptr<EngineSampler> Load(std::string_view ShaderName, D3D11_SAMPLER_DESC Desc);
	inline ID3D11SamplerState* GetSamplerState()
	{
		return SamplerState;
	}

protected:

private:
	D3D11_SAMPLER_DESC SamplerDesc = {};
	ID3D11SamplerState* SamplerState = nullptr;

};

