Texture2D<float4> inputTexture : register(t0);
RWTexture2D<float4> outputTexture : register(u0);

cbuffer FilterBuffer : register(b0)
{
	float luminance;
	float middleGray;
	float whiteCutoff;
	float padding;
}

float gray(float4 c)
{
	return dot(c.rgb, (0.33333f).xxx);
}

float4 filter(float4 color)
{
	float3 colorOut = color.xyz;

	colorOut *= middleGray / (luminance + 0.001f);
	colorOut *= (1.0f + (colorOut / (whiteCutoff * whiteCutoff)));
	colorOut -= 5.0f;

	colorOut = max(colorOut, 0.0f);

	colorOut /= (10.0f + colorOut);

	return float4(colorOut, 1.0f);
}

[numthreads(32, 32, 1)]
void main(uint3 tid : SV_DispatchThreadID)
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	color += filter(inputTexture[uint2(tid.x * 2, tid.y * 2)]);
	color += filter(inputTexture[uint2(tid.x * 2 + 1, tid.y * 2)]);
	color += filter(inputTexture[uint2(tid.x * 2 + 1, tid.y * 2)]);
	color += filter(inputTexture[uint2(tid.x * 2, tid.y * 2 + 1)]);

	color /= 4.0f;
	color.w = 1.0f;
	outputTexture[tid.xy] = color;
}