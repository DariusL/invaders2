Texture2D shaderTexture : register(t0);
SamplerState samplerType : register(s0);

cbuffer KernelBuffer : register(b2)
{
	float3x3 kernelx;
	float3x3 kernely;
	float offset;
	float3 xOffset;
	float3 yOffset;
	float3 padding;
}

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
	[unroll]
	for (int x = 0; x < 3; x++)
	{
		[unroll]
		for (int y = 0; y < 3; y++)
		{
			ColorX += kernely[x][y] * pixels[x][y];
			ColorY += kernelx[x][y] * pixels[x][y];
		}
	}
	return sqrt(ColorX * ColorX + ColorY * ColorY);
}

float4 main(PixelInputType input) : SV_TARGET
{
	float3x3 nearbyPixels;
	[unroll]
	for (int x = 0; x < 3; x++)
	{
		[unroll]
		for (int y = 0; y < 3; y++)
		{
			nearbyPixels[x][y] = shaderTexture.Sample(samplerType, input.tex + float2(xOffset[x], yOffset[y])).x;
		}
	}
	int clipped = round(sobelSum(nearbyPixels) + offset);
	float result = !clipped;
	return shaderTexture.Sample(samplerType, input.tex) * float4(result.xxx, 1);
}