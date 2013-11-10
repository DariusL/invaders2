Texture2D reflectionTexture : register(t0);
Texture2D refractionTexture : register(t1);
Texture2D normalTexture : register(t2);

SamplerState SampleType;

cbuffer WaterBuffer : register(b0)
{
	float2 waterTranslation;
	float scale;
	float padding;
}

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 reflectionPos : TEXCOORD1;
	float4 refractionPos : TEXCOORD2;
	float3 cameraDir : POSITION0;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float2 reflextTex;
	float2 refractTex;
    float4 normalMap;
    float3 normal;
    float4 reflectionColor;
    float4 refractionColor;

	input.tex += waterTranslation;

	reflextTex.x = input.reflectionPos.x / input.reflectionPos.w / 2.0f + 0.5f;
	reflextTex.y = -input.reflectionPos.y / input.reflectionPos.w / 2.0f + 0.5f;
	
	refractTex.x = input.refractionPos.x / input.refractionPos.w / 2.0f + 0.5f;
	refractTex.y = -input.refractionPos.y / input.refractionPos.w / 2.0f + 0.5f;

    normalMap = normalTexture.Sample(SampleType, input.tex);

    normal = (normalMap.xyz * 2.0f) - 1.0f;

    reflextTex = reflextTex + (normal.xy * scale);
    refractTex = refractTex + (normal.xy * scale);

    reflectionColor = reflectionTexture.Sample(SampleType, reflextTex);
    refractionColor = refractionTexture.Sample(SampleType, refractTex);
	
	return lerp(reflectionColor, refractionColor, 0.6f);
}