#include "PrecompileHeader.h"
#include "EngineTransform.h"

EngineTransform::EngineTransform() 
{
}

EngineTransform::~EngineTransform() 
{
}

void EngineTransform::TransformUpdate()
{
	CalLocalTransform();
	WorldMatrix = LocalMatrix;
	if (Parent != nullptr)
	{
		CalWorldTransform();
	}
	WorldDecompose();
}

void EngineTransform::CalLocalTransform()
{
	LocalRad = float4::Deg2Rad(LocalRotation);
	LocalQuaternion = float4::Rad2Quaternion(LocalRad);
	LocalMatrix = float4x4::Compose(LocalScale, LocalRad, LocalQuaternion, LocalPosition);
}

void EngineTransform::CalWorldTransform()
{
	WorldMatrix = LocalMatrix * Parent->WorldMatrix;
}

void EngineTransform::UpdateLocalFromWorld()
{
	WorldRad = float4::Deg2Rad(WorldRotation);
	WorldQuaternion = float4::Rad2Quaternion(WorldRad);
	WorldMatrix = float4x4::Compose(WorldScale, WorldRad, WorldQuaternion, WorldPosition);

	if (Parent != nullptr)
	{
		//�θ������ ����� ���ϰ�, ���� ���忡 ���ؼ� ������ ����
		float4x4 ParentWorldInverse = Parent->GetWorldMatrix();
		ParentWorldInverse.Inverse();
		LocalMatrix = WorldMatrix * ParentWorldInverse;
	}

	//���� ����������
	LocalDecompose();
}

void EngineTransform::WorldDecompose()
{
	WorldMatrix.Decompose(WorldScale, WorldQuaternion, WorldPosition);
	WorldRad = float4::Quaternion2Rad(WorldQuaternion);
	WorldRotation = float4::Rad2Deg(WorldRad);
}

void EngineTransform::LocalDecompose()
{
	LocalMatrix.Decompose(LocalScale, LocalQuaternion, LocalPosition);
	LocalRad = float4::Quaternion2Rad(LocalQuaternion);
	LocalRotation = float4::Rad2Deg(LocalRad);
}

void EngineTransform::SetMaster(std::shared_ptr<EngineObject> MasterPtr)
{
	Master = MasterPtr;
}


