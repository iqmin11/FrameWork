#pragma once
namespace EngineMath
{

};

struct float4
{
	//Optional///////////////////////////
	inline static float4 Zero()
	{
		return { 0.f,0.f,0.f,1.f };
	}

	inline static float4 MinusOne()
	{
		return { -1.f,-1.f,-1.f,-1.f };
	}

	inline int ix() const
	{
		return static_cast<int>(x);
	}

	inline int iy() const
	{
		return static_cast<int>(y);
	}

	inline int iz() const
	{
		return static_cast<int>(z);
	}

	//Operator///////////////////////////
	bool operator== (const float4& Right)
	{
		return (x == Right.x && y == Right.y && z == Right.z && w == Right.w);
	}

	//Property///////////////////////////
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 1.f;
}; 
