Texture2D<float4> inputTexture : register(t0);
RWTexture2D<float4> outputTexture : register(u0);

cbuffer KernelBuffer : register(b1)
{
	float4x4 kernelx;
	float4x4 kernely;
};

cbuffer OffsetBuffer : register(b2)
{
	float offset;
	float3 padding;
};

float sobelSum(float3x3 pixels)
{
	float ColorX = 0;
	float ColorY = 0;

	//spalvos pokytis x ir y kryptimis pagal sobel operator
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

float gray(float4 c)
{
	return dot(c.rgb, (0.33333f).xxx);
}

[numthreads(32, 32, 1)]
void main( uint3 tid : SV_DispatchThreadID )
{
	//3x3 pixeliu matrica
	float3x3 nearbyPixels;
	nearbyPixels._11 = gray(inputTexture[tid.xy + float2(-1.0f, -1.0f)]);
	nearbyPixels._12 = gray(inputTexture[tid.xy + float2(0.0f, -1.0f)]);
	nearbyPixels._13 = gray(inputTexture[tid.xy + float2(1.0f, -1.0f)]);

	nearbyPixels._21 = gray(inputTexture[tid.xy + float2(-1.0f, 0.0f)]);
	nearbyPixels._22 = gray(inputTexture[tid.xy + float2(0.0f, 0.0f)]);
	nearbyPixels._23 = gray(inputTexture[tid.xy + float2(1.0f, 0.0f)]);

	nearbyPixels._31 = gray(inputTexture[tid.xy + float2(-1.0f, 1.0f)]);
	nearbyPixels._32 = gray(inputTexture[tid.xy + float2(0.0f, 1.0f)]);
	nearbyPixels._33 = gray(inputTexture[tid.xy + float2(1.0f, 1.0f)]);

	//result = 0.0f jei cia briauna
	int clipped = round(sobelSum(nearbyPixels) + offset);
	float result = !clipped;
	outputTexture[tid.xy] = inputTexture[tid.xy] * float4(result.xxx, 1.0f);
}