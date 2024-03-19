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

	inline int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	inline int uiy() const
	{
		return static_cast<unsigned int>(y);
	}

	inline int uiz() const
	{
		return static_cast<unsigned int>(z);
	}

	//Operator///////////////////////////
	bool operator== (const float4& Right)
	{
		return (x == Right.x && y == Right.y && z == Right.z && w == Right.w);
	}

	//Property///////////////////////////
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		struct
		{
			float PosX;
			float PosY;
			float SizeX;
			float SizeY;
		};	

		float Arr1D[4];
	};

	//Constructor///////////////////////////
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

}; 
