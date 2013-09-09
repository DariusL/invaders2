cbuffer TransMatrix : register(b0)
{
    matrix transform;
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	output.tex = input.tex;
	output.position = mul(input.position, transform);
	return output;
}