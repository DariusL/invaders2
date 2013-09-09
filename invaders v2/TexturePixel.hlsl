Texture2D shaderTexture : register(t0);
SamplerState samplerType : register(s0);

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 main(PixelInputType input) : SV_TARGET
{
	return shaderTexture.Sample(samplerType, input.tex);
}