cbuffer TransMatrix : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer ReflectionBuffer : register(b1)
{
	matrix reflectView;
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
	matrix reflectProjectWorld;
	output.tex = input.tex;
	input.position.w = 1.0f;
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.reflectionPos = input.position;
	output.reflectionPos = mul(output.reflectionPos, world);
	output.reflectionPos = mul(output.reflectionPos, reflectView);
	output.reflectionPos = mul(output.reflectionPos, projection);
	return output;
}