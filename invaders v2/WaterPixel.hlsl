Texture2D reflectionTexture;
Texture2D refractionTexture;
Texture2D normalTexture;

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
	float4 reflectionMapPos : TEXCOORD1;
	float4 refractionMapPos : TEXCOORD2;
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

    reflextTex.x = input.reflectionMapPos.x / input.reflectionMapPos.w / 2.0f + 0.5f;
    reflextTex.y = -input.reflectionMapPos.y / input.reflectionMapPos.w / 2.0f + 0.5f;
	
    refractTex.x = input.refractionMapPos.x / input.refractionMapPos.w / 2.0f + 0.5f;
    refractTex.y = -input.refractionMapPos.y / input.refractionMapPos.w / 2.0f + 0.5f;

    normalMap = normalTexture.Sample(SampleType, input.tex);

    normal = (normalMap.xyz * 2.0f) - 1.0f;

    reflextTex = reflextTex + (normal.xy * scale);
    refractTex = refractTex + (normal.xy * scale);

    // Sample the texture pixels from the textures using the updated texture coordinates.
    reflectionColor = reflectionTexture.Sample(SampleType, reflextTex);
    refractionColor = refractionTexture.Sample(SampleType, refractTex);
	
    return lerp(reflectionColor, refractionColor, 0.6f);
}