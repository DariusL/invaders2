cbuffer TransMatrix : register(b0)
{
	matrix transform;
};

cbuffer ReflectionBuffer : register(b1)
{
	matrix reflectionTransform;
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
	float4 reflectionPos : TEXCOORD1;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	output.tex = input.tex;
	output.position = mul(input.position, transform);
	output.reflectionPos = mul(input.position, reflectionTransform);
	return output;
}