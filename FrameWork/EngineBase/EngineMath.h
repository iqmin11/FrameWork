#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>

// dx함수들
// 다이렉트용 벡터
#include <DirectXMath.h>

class EngineMath
{
public:
	static const float PI;
	static const float PI2;

	static float Rad2Deg(float Rad)
	{
		return (180.0f / PI) * Rad;
	}

	static float Deg2Rad(float Deg)
	{
		return (PI / 180.0f) * Deg;
	}

private:
	virtual ~EngineMath() = 0;
};

struct alignas(16) float4
{
	static const float4 ZERO;
	static const float4 ZERONULL;
	static const float4 ONE;
	static const float4 BLACK;
	static const float4 WHITE;
	static const float4 RED;
	static const float4 GREEN;
	static const float4 BLUE;

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
			float left;
			float top;
			float right;
			float bottom;
		};

		float Arr1D[4];
		DirectX::XMFLOAT4 DirectFloat4;
		DirectX::XMVECTOR DirectVector;
	};

	operator DirectX::FXMVECTOR() const
	{
		return DirectVector;
	}

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


	unsigned int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	unsigned int uiy() const
	{
		return static_cast<unsigned int>(y);
	}

	unsigned int uiz() const
	{
		return static_cast<unsigned int>(z);
	}

	unsigned int uiw() const
	{
		return static_cast<unsigned int>(w);
	}

	unsigned int uhix() const
	{
		return static_cast<unsigned int>(x * 0.5f);
	}

	unsigned int uhiy() const
	{
		return static_cast<unsigned int>(y * 0.5f);
	}

	unsigned int uhiz() const
	{
		return static_cast<unsigned int>(z * 0.5f);
	}

	unsigned int uhiw() const
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

	static float4 Deg2Rad(const float4& Deg)
	{
		return float4(EngineMath::Deg2Rad(Deg.x), EngineMath::Deg2Rad(Deg.y), EngineMath::Deg2Rad(Deg.z), 0.0f);
	}

	static float4 Rad2Deg(const float4& Rad)
	{
		return float4(EngineMath::Rad2Deg(Rad.x), EngineMath::Rad2Deg(Rad.y), EngineMath::Rad2Deg(Rad.z), 0.0f);
	}

	static float4 Rad2Quaternion(const float4& Rad)
	{
		float4 Ret;
		Ret.DirectVector = DirectX::XMQuaternionRotationRollPitchYawFromVector(Rad);
		return Ret;
	}

	static float4 Quaternion2Rad(const float4& Quat)
	{
		float4 Ret;
		const float& x = Quat.x;
		const float& y = Quat.y;
		const float& z = Quat.z;
		const float& w = Quat.w;

		float sinrCosp = 2.0f * (w * z + x * y);
		float cosrCosp = 1.0f - 2.0f * (z * z + x * x);
		Ret.z = atan2f(sinrCosp, cosrCosp);

		float pitchTest = w * x - y * z;
		float asinThreshold = 0.4999995f;
		float sinp = 2.0f * pitchTest;

		if (pitchTest < -asinThreshold)
		{
			Ret.x = -(0.5f * EngineMath::PI);
		}
		else if (pitchTest > asinThreshold)
		{
			Ret.x = (0.5f * EngineMath::PI);
		}
		else
		{
			Ret.x = asinf(sinp);
		}

		float sinyCosp = 2.0f * (w * y + x * z);
		float cosyCosp = 1.0f - 2.0f * (x * x + y * y);
		Ret.y = atan2f(sinyCosp, cosyCosp);

		return Ret;
	}
};

struct float4x4
{
	static const float4x4 IdentityMatrix;

	float4x4()
		: DirectMatrix(DirectX::XMMatrixIdentity())
	{

	}

	float4x4(const DirectX::XMMATRIX& Other)
		: DirectMatrix(Other)
	{

	}

	union
	{
		DirectX::XMMATRIX DirectMatrix;

		struct
		{
			float _11;
			float _12;
			float _13;
			float _14;
			float _21;
			float _22;
			float _23;
			float _24;
			float _31;
			float _32;
			float _33;
			float _34;
			float _41;
			float _42;
			float _43;
			float _44;
		};

		float Arr1D[16];
		float Arr2D[4][4];
		float4 VectorArr[4];
	};

	operator DirectX::FXMMATRIX() const
	{
		return DirectMatrix;
	}

	static float4x4 Compose(const float4& Scale, const float4& Rad, const float4& Quaternion, const float4& Pos)
	{
		return DirectX::XMMatrixAffineTransformation(Scale, Rad, Quaternion, Pos);
	}

	void Decompose(float4& OutScale, float4& OutQuat, float4& OutPos)
	{
		DirectX::XMMatrixDecompose(&OutScale.DirectVector, &OutQuat.DirectVector, &OutPos.DirectVector, *this);
	}

	static float4x4 Inverse(const float4x4& Matrix)
	{
		float4x4 Ret = Matrix;
		return DirectX::XMMatrixInverse(nullptr, Ret);
	}

	void Inverse()
	{
		DirectX::XMMatrixInverse(nullptr, *this);
	}

	float4x4 operator*(const float4x4& Other)
	{
		return DirectX::XMMatrixMultiply(*this, Other);
	}

};




