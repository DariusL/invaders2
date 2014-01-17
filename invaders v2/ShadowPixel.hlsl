SamplerState sampleType : register(s0);
SamplerComparisonState shadowSampleType : register(s1);

Texture2D shaderTexture : register(t0);
Texture2D depthMap : register(t1);

cbuffer LightBuffer : register(b0)
{
	float4 diffuse;
	float4 ambient;
	float border;
	float3 padding;
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

	//koordinates transformuojamos projektavimui
	input.lightViewPosition.xyz /= input.lightViewPosition.w;
	input.lightViewPosition.y = -input.lightViewPosition.y;
	input.lightViewPosition.xy = (input.lightViewPosition.xy + float2(1.0f, 1.0f)) / 2.0f;
	float shadow;
	//uz sviesos daros nesamones su koordinatem
	//baisu, bet nesugalvojau kaip kitaip padaryt
	if (input.lightViewPosition.w >= 0.1f)
		shadow = depthMap.SampleCmp(shadowSampleType, input.lightViewPosition.xy, input.lightViewPosition.z - bias);
	else
		shadow = border;

	float lightIntensity = saturate(dot(normalize(input.normal), input.lightDir));

	color = (saturate(diffuse * lightIntensity * shadow) + ambient) * shaderTexture.Sample(sampleType, input.tex);
	color.w = 1.0f;

	return color;
}