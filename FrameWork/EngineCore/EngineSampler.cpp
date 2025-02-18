#include "PrecompileHeader.h"
#include "EngineSampler.h"

EngineSampler::EngineSampler() 
{
}

EngineSampler::~EngineSampler() 
{
    if (SamplerState != nullptr)
    {
        SamplerState->Release();
    }
}

std::shared_ptr<EngineSampler> EngineSampler::Load(std::string_view SamplerName, D3D11_SAMPLER_DESC Desc)
{
    std::shared_ptr<EngineSampler> NewSampler = Create(SamplerName);

    NewSampler->SamplerDesc = Desc;

    HRESULT Result = EngineDevice::GetDevice()->CreateSamplerState(&(NewSampler->SamplerDesc), &(NewSampler->SamplerState));
    assert(SUCCEEDED(Result));

    return NewSampler;
}

