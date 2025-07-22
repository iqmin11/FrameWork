#include "PrecompileHeader.h"
#include "EngineMath.h"

// �������� ���ڰ� �տ��ü��� �����ϴ�.

const float EngineMath::PI = DirectX::XM_PI;
const float EngineMath::PI2 = DirectX::XM_2PI;

const float4 float4::ZERO = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::ZERONULL = { 0.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::ONE = { 1.0f, 1.0f, 1.0f, 1.0f };
const float4 float4::BLACK = float4::ZERO;
const float4 float4::WHITE = float4::ONE;
const float4 float4::RED = {1.0f, 0.0f, 0.0f, 1.0f};
const float4 float4::GREEN = {0.0f, 1.0f, 0.0f, 1.0f};
const float4 float4::BLUE = {0.0f, 0.0f, 1.0f, 1.0f};

const float4x4 float4x4::IdentityMatrix = float4x4();
