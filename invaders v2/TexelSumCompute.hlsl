Texture2D<float4> inputTexture1 : register(t0);
Texture2D<float4> inputTexture2 : register(t1);
RWTexture2D<float4> outputTexture : register(u0);

[numthreads(32, 32, 1)]
void main(uint3 tid : SV_DispatchThreadID)
{
	outputTexture[tid.xy] = inputTexture1[tid.xy] + inputTexture2[tid.xy];
}