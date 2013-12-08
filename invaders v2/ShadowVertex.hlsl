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

cbuffer LightBuffer : register(b2)
{
	matrix lightView;
	matrix lightpProject;
	float3 lightPos;
	float padding;
}

cbuffer InverseMatrixBuffer : register(b3)
{
	matrix inverseWorld;
}

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float4 lightViewPosition : TEXCOORD1;
	float3 lightDir : TEXCOORD2;
};

[clipplanes(clip)]
PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	input.position.w = 1.0f;

	output.position = mul(input.position, world);
	float4 worldPos = output.position;
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.lightViewPosition = mul(worldPos, lightView);
	output.lightViewPosition = mul(output.lightViewPosition, lightpProject);

	output.normal = mul(input.normal, (float3x3)inverseWorld);
	output.lightDir = normalize(lightPos.xyz - worldPos.xyz);
	output.tex = input.tex;
	return output;
}