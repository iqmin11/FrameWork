
struct VS_Input
{
    float4 pos : POS;
    float4 uv : TEX;
    float4 color : COL;
};

struct VS_Output
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float4 color : COL;
};

Texture2D mytexture : register(t0);
SamplerState mysampler : register(s0);

VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.position = input.pos;
    output.uv = (float2)input.uv;
    output.color = input.color;
    
    return output;
}

float4 ps_main(VS_Output input) : SV_Target
{
    return mytexture.Sample(mysampler, input.uv);
}