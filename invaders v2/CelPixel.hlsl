Texture2D shaderTexture : register(t0);
SamplerState samplerType : register(s0);

cbuffer KernelBuffer : register(b0)
{
	float4x4 kernelx;
	float4x4 kernely;
};

cbuffer OffsetBuffer : register(b1)
{
	float3 xOffset;
	float offset;
	float3 yOffset;
	float padding;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float sobelSum(float3x3 pixels)
{
	float ColorX = 0;
	float ColorY = 0;
	// Convolution operation. Matrix elements with same coords are multiplied and added to result

	ColorX += kernely._11 * pixels._11;
	ColorY += kernelx._11 * pixels._11;
	ColorX += kernely._12 * pixels._12;
	ColorY += kernelx._12 * pixels._12;
	ColorX += kernely._13 * pixels._13;
	ColorY += kernelx._13 * pixels._13;

	ColorX += kernely._21 * pixels._21;
	ColorY += kernelx._21 * pixels._21;
	ColorX += kernely._22 * pixels._22;
	ColorY += kernelx._22 * pixels._22;
	ColorX += kernely._23 * pixels._23;
	ColorY += kernelx._23 * pixels._23;

	ColorX += kernely._31 * pixels._31;
	ColorY += kernelx._31 * pixels._31;
	ColorX += kernely._32 * pixels._32;
	ColorY += kernelx._32 * pixels._32;
	ColorX += kernely._33 * pixels._33;
	ColorY += kernelx._33 * pixels._33;

	return sqrt(ColorX * ColorX + ColorY * ColorY);
}

float getGray(float4 c)
{
	return dot(c.rgb, (0.33333f).xxx);
}

float4 main(PixelInputType input) : SV_TARGET
{
	float3x3 nearbyPixels;
	nearbyPixels._11 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.x, yOffset.x)));
	nearbyPixels._12 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.y, yOffset.x)));
	nearbyPixels._13 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.z, yOffset.x)));

	nearbyPixels._21 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.x, yOffset.y)));
	nearbyPixels._22 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.y, yOffset.y)));
	nearbyPixels._23 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.z, yOffset.y)));

	nearbyPixels._31 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.x, yOffset.z)));
	nearbyPixels._32 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.y, yOffset.z)));
	nearbyPixels._33 = getGray(shaderTexture.Sample(samplerType, input.tex + float2(xOffset.z, yOffset.z)));

	int clipped = round(sobelSum(nearbyPixels) + offset);
	float result = !clipped;
	//float result = (sobelSum(nearbyPixels) + offset;
	return shaderTexture.Sample(samplerType, input.tex) * float4(result.xxx, 1.0f);
	//return float4(result.xxx, 1.0f);
}