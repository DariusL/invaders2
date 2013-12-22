Texture2D<float4> inputTexture : register(t0);
RWTexture2D<float4> outputTexture : register(u0);

cbuffer FilterBuffer : register(b0)
{
	float threshold;
	float3 padding;
}

float gray(float4 c)
{
	return dot(c.rgb, (0.33333f).xxx);
}

int filter(float4 color)
{
	float brightness = gray(color);
	return round(brightness - threshold + 0.5f);
}

[numthreads(32, 32, 1)]
void main(uint3 tid : SV_DispatchThreadID)
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 temp;

	temp = inputTexture[uint2(tid.x * 2, tid.y * 2)];
	color += temp * filter(temp);

	temp = inputTexture[uint2(tid.x * 2 + 1, tid.y * 2)];
	color += temp * filter(temp);

	temp = inputTexture[uint2(tid.x * 2 + 1, tid.y * 2)];
	color += temp * filter(temp);

	temp = inputTexture[uint2(tid.x * 2, tid.y * 2 + 1)];
	color += temp * filter(temp);

	color /= 4.0f;
	color.w = 1.0f;
	outputTexture[tid.xy] = color;
}