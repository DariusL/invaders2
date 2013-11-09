Texture2D reflectionTexture : register(t0);
SamplerState samplerType : register(s0);

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 reflectionPos : TEXCOORD1;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float2 reflectTex;

	reflectTex.x = input.reflectionPos.x / input.reflectionPos.w / 2.0f + 0.5f;
	reflectTex.y = -input.reflectionPos.y / input.reflectionPos.w / 2.0f + 0.5f;

	//reflectTex = input.tex;

	return reflectionTexture.Sample(samplerType, reflectTex);
}