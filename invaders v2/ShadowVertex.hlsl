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
	matrix lightProject;
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
	float4 shadowPos = worldPos;
	shadowPos = mul(shadowPos, lightView);
	shadowPos = mul(shadowPos, lightProject);
	shadowPos.xyz /= shadowPos.w;
	shadowPos.y = -shadowPos.y;
	shadowPos.xy = (shadowPos.xy + float2(1.0f, 1.0f)) / 2.0f;

	output.lightViewPosition = shadowPos;

	output.normal = mul(input.normal, (float3x3)inverseWorld);
	output.lightDir = normalize(lightPos.xyz - worldPos.xyz);
	output.tex = input.tex;
	return output;
}