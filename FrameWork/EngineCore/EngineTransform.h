#pragma once
#include "EngineBase/EngineMath.h"

// ���� :
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

	void TrasnformUpdate();

protected:

private:
	float4 Scale = float4::ONE;
	float4 Rotation = float4::ZERO; // Euler
	float4 Position = float4::ZERO;

	float4x4 LocalMatrix; //ũ����
	float4x4 WorldMatrix; //����

	std::shared_ptr<EngineTransform> Parent;

	void CalLocalTransform();
	void CalWorldTransform();
};

