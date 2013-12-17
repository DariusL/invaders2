cbuffer TransMatrix : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer ClipBuffer : register(b1)
{
	float4 clip;
}

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

[clipplanes(clip)]
PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	output.tex = input.tex;
	input.position.w = 1.0f;
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	return output;
}