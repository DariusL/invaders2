Texture2D shaderTexture : register(t0);
SamplerState samplerType : register(s0);

cbuffer BlurBuffer : register(b0)
{
	float4 offset;
	float4 weight;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	color += shaderTexture.Sample(samplerType, input.tex + float2(offset.y, 0.0f)) * weight.x;

	color += shaderTexture.Sample(samplerType, input.tex + float2(offset.x * 1.0f, 0.0f)) * weight.y;
	color += shaderTexture.Sample(samplerType, input.tex + float2(offset.x * 2.0f, 0.0f)) * weight.z;
	color += shaderTexture.Sample(samplerType, input.tex + float2(offset.x * 3.0f, 0.0f)) * weight.w;

	color += shaderTexture.Sample(samplerType, input.tex + float2(offset.z * 1.0f, 0.0f)) * weight.y;
	color += shaderTexture.Sample(samplerType, input.tex + float2(offset.z * 2.0f, 0.0f)) * weight.z;
	color += shaderTexture.Sample(samplerType, input.tex + float2(offset.z * 3.0f, 0.0f)) * weight.w;

	color.w = 1.0f;
	return color;
}