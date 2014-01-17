Texture2D reflectionTexture : register(t0);
Texture2D refractionTexture : register(t1);
Texture2D normalTexture : register(t2);

SamplerState sampleType : register(s0);
SamplerState waterSampleType : register(s1);

#define derp lerp

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

	//vanduo juda
	input.tex += waterTranslation;

	//projektuojamo atspindzio koordinates
	reflextTex.x = input.reflectionPos.x / input.reflectionPos.w / 2.0f + 0.5f;
	reflextTex.y = -input.reflectionPos.y / input.reflectionPos.w / 2.0f + 0.5f;
	
	//projektuojamo permatomo vaizdo koordinates
	refractTex.x = input.refractionPos.x / input.refractionPos.w / 2.0f + 0.5f;
	refractTex.y = -input.refractionPos.y / input.refractionPos.w / 2.0f + 0.5f;

    normalMap = normalTexture.Sample(sampleType, input.tex);
    normal = (normalMap.xyz * 2.0f) - 1.0f;

	//projektuojamos koordinates perstumiamos pagal normal map
    reflextTex = reflextTex + (normal.xy * scale);
    refractTex = refractTex + (normal.xy * scale);

	reflectionColor = reflectionTexture.Sample(waterSampleType, reflextTex);
	refractionColor = refractionTexture.Sample(waterSampleType, refractTex);

	//lerp - linear interpolation
	return derp(refractionColor, reflectionColor, 0.6f);
}