#pragma once
#include "EngineBase/EngineMath.h"

// 설명 :
class EngineObject;
class EngineTransform : public std::enable_shared_from_this<EngineTransform>
{
	friend class EngineObject;

public:
	// constrcuter destructer
	EngineTransform();
	~EngineTransform();

	// delete Function
	EngineTransform(const EngineTransform& _Other) = delete;
	EngineTransform(EngineTransform&& _Other) noexcept = delete;
	EngineTransform& operator=(const EngineTransform& _Other) = delete;
	EngineTransform& operator=(EngineTransform&& _Other) noexcept = delete;

	inline void SetLocalScale(const float4& Scale)
	{
		LocalScale = Scale;
	}

	inline void SetLocalRotation(const float4& Deg)
	{
		LocalRotation = Deg;
	}

	inline void SetLocalPosition(const float4& Pos)
	{
		LocalPosition = Pos;
	}

	inline void SetWorldScale(const float4& Scale)
	{
		WorldScale = Scale;
		UpdateLocalFromWorld();
	}

	inline void SetWorldRotation(const float4& Deg)
	{
		WorldRotation = Deg;
		UpdateLocalFromWorld();
	}

	inline void SetWorldPosition(const float4& Pos)
	{
		WorldPosition = Pos;
		UpdateLocalFromWorld();
	}

	inline const float4x4& GetWorldMatrix() const
	{
		return WorldMatrix;
	}

	void SetParent(std::shared_ptr<EngineTransform> ParentTransform)
	{
		if (!Parent.expired())
		{
			//TODO : 원래 세팅된 부모를 제거하고 옮기는 기능
			MsgAssert("기능 추가 필요")
		}

		ParentTransform->Childs.push_back(shared_from_this());
		Parent = ParentTransform;
	}

	const std::shared_ptr<EngineTransform> GetParent() const
	{
		return Parent.lock();
	}

	const std::shared_ptr<class EngineObject> GetMaster() const;

	void TransformUpdate();

protected:

private:
	float4 LocalScale = float4::ONE;
	float4 LocalRotation = float4::ZERONULL; // Euler Deg
	float4 LocalRad = float4::ZERONULL;
	float4 LocalQuaternion = float4::ZERONULL;
	float4 LocalPosition = float4::ZERO;

	float4 WorldScale = float4::ONE;
	float4 WorldRotation = float4::ZERONULL; // Euler Deg
	float4 WorldRad = float4::ZERONULL;
	float4 WorldQuaternion = float4::ZERONULL;
	float4 WorldPosition = float4::ZERO;

	float4x4 LocalMatrix; //부모 0,0 기준 좌표
	float4x4 WorldMatrix; //월드 0,0 기준 좌표

	std::weak_ptr<EngineObject> Master;
	std::weak_ptr<EngineTransform> Parent;
	std::vector<std::shared_ptr<EngineTransform>> Childs;
	
	void CalLocalTransform();
	void CalWorldTransform();

	void UpdateLocalFromWorld();
	void WorldDecompose();
	void LocalDecompose();

	void SetMaster(std::shared_ptr<EngineObject> MasterPtr); // object를 만들때 호출해야하는 함수
};

