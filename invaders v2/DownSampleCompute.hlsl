Texture2D<float4> inputTexture : register(t0);
RWTexture2D<float4> outputTexture : register(u0);

[numthreads(32, 32, 1)]
void main(uint3 tid : SV_DispatchThreadID)
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	color += inputTexture[uint2(tid.x * 2, tid.y * 2)];
	color += inputTexture[uint2(tid.x * 2 + 1, tid.y * 2)];
	color += inputTexture[uint2(tid.x * 2 + 1, tid.y * 2)];
	color += inputTexture[uint2(tid.x * 2, tid.y * 2 + 1)];
	color /= 4.0f;
	color.w = 1.0f;
	outputTexture[tid.xy] = color;
}