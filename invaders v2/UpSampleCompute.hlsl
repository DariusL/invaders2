Texture2D<float4> inputTexture : register(t0);
RWTexture2D<float4> outputTexture : register(u0);

[numthreads(32, 32, 1)]
void main(uint3 tid : SV_DispatchThreadID)
{
	outputTexture[tid.xy] = inputTexture[tid.xy / 2];
}