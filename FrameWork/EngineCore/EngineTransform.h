#pragma once

struct TransformData
{
	TransformData()
	{
		Scale = float4::ONE;
		Rotation = float4::ZERONULL;
		Quaternion = float4::ZERONULL;
		Position = float4::ZERO;
	}

	// 계산을 위한 편의용 스케일
	float4 Scale;
	float4 Rotation;
	float4 Quaternion;
	float4 Position;

	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalQuaternion;
	float4 LocalPosition;

	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldQuaternion;
	float4 WorldPosition;

	float4x4 ScaleMatrix;
	float4x4 RotationMatrix;
	float4x4 PositionMatrix;
	float4x4 LocalWorldMatrix;
	float4x4 WorldMatrix;
	float4x4 View;
	float4x4 Projection;
	float4x4 ViewPort;
	float4x4 WorldView;
	float4x4 WorldViewProjectionMatrix;

};

// 설명 :
class EngineTransform
{
public:
	// constrcuter destructer
	EngineTransform();
	~EngineTransform();

	// delete Function
	EngineTransform(const EngineTransform& _Other) = delete;
	EngineTransform(EngineTransform&& _Other) noexcept = delete;
	EngineTransform& operator=(const EngineTransform& _Other) = delete;
	EngineTransform& operator=(EngineTransform&& _Other) noexcept = delete;

protected:

private:

	TransformData Data;
};

