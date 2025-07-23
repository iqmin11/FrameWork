#include "PrecompileHeader.h"
#include "EngineCore.h"

#include "EngineTexture.h"
#include "EngineViewportTarget.h"
#include "EngineInputLayout.h"
#include "EngineStaticMeshVertex.h"
#include "EngineDynamicMeshVertex.h"

void EngineCore::CoreResourceInit()
{
	//����ƽ �޽� ��ǲ ���̾ƿ� desc ����
	{
		EngineStaticMeshVertex::InputLayoutData.AddInputElement("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineStaticMeshVertex::InputLayoutData.AddInputElement("TEXCOORD", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineStaticMeshVertex::InputLayoutData.AddInputElement("COLOR", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineStaticMeshVertex::InputLayoutData.AddInputElement("NORMAL", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineStaticMeshVertex::InputLayoutData.AddInputElement("BINORMAL", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineStaticMeshVertex::InputLayoutData.AddInputElement("TANGENT", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
	}

	//���̳��� �޽� ��ǲ ���̾ƿ� desc ����
	{
		EngineDynamicMeshVertex::InputLayoutData.AddInputElement("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineDynamicMeshVertex::InputLayoutData.AddInputElement("TEXCOORD", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineDynamicMeshVertex::InputLayoutData.AddInputElement("COLOR", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineDynamicMeshVertex::InputLayoutData.AddInputElement("NORMAL", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineDynamicMeshVertex::InputLayoutData.AddInputElement("BINORMAL", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineDynamicMeshVertex::InputLayoutData.AddInputElement("TANGENT", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineDynamicMeshVertex::InputLayoutData.AddInputElement("BLENDWEIGHT", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
		EngineDynamicMeshVertex::InputLayoutData.AddInputElement("BLENDINDICES", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT);
	}
}

void EngineCore::CoreResourceRelease()
{
	EngineTexture::Release();
	EngineViewportTarget::Release();
}