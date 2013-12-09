SamplerState sampleType : register(s0);
SamplerComparisonState shadowSampleType : register(s1);

Texture2D shaderTexture : register(t0);
Texture2D depthMap : register(t1);

cbuffer LightBuffer : register(b0)
{
	float4 diffuse;
	float4 ambient;
}

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float4 lightViewPosition : TEXCOORD1;
	float3 lightDir : TEXCOORD2;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float bias = 0.001f;
	float4 color;
	float2 projectTexCoord;

	projectTexCoord.x = input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;

	float shadow = depthMap.SampleCmp(shadowSampleType, projectTexCoord, input.lightViewPosition.z - bias);

	float lightIntensity = saturate(dot(normalize(input.normal), input.lightDir));

	color = (saturate(diffuse * lightIntensity * shadow) + ambient) * shaderTexture.Sample(sampleType, input.tex);

	return color;
}