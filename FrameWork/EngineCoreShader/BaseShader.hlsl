
struct VS_Input
{
    float4 pos : POS;
    float4 color : COL;
};

struct VS_Output
{
    float4 position : SV_POSITION;
    float4 color : COL;
};

VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.position = input.pos;
    output.color = input.color;
    
    return output;
}

float4 ps_main(VS_Output input) : SV_Target
{
    return input.color;
}