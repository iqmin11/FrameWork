#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>

// dx함수들
// 다이렉트용 벡터
#include <DirectXMath.h>

// final 더이상 상속내릴지 못한다.
// 상속도 못하고 만들지도 못하게 만든 상태로

class EngineMath final
{
public:

private:
	virtual ~EngineMath() = 0;
};

struct float4
{
	static const float4 ZERO;

public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float Arr1D[4];
	};

	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}

	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}


	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float hw() const
	{
		return w * 0.5f;
	}


	int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	int uiy() const
	{
		return static_cast<unsigned int>(y);
	}

	int uiz() const
	{
		return static_cast<unsigned int>(z);
	}

	int uiw() const
	{
		return static_cast<unsigned int>(w);
	}

	int uhix() const
	{
		return static_cast<unsigned int>(x * 0.5f);
	}

	int uhiy() const
	{
		return static_cast<unsigned int>(y * 0.5f);
	}

	int uhiz() const
	{
		return static_cast<unsigned int>(z * 0.5f);
	}

	int uhiw() const
	{
		return static_cast<unsigned int>(w * 0.5f);
	}

	POINT ToWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	float4 half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,w };
	}

};


