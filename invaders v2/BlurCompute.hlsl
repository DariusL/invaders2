Texture2D<float4> inputTexture : register(t0);
RWTexture2D<float4> outputTexture : register(u0);

cbuffer BlurBuffer : register(b1)
{
	float4 weight;
	uint2 off1;
	uint2 off2;
	uint2 off3;
	uint2 padding;
};

[numthreads(32, 32, 1)]
void main(uint3 tid : SV_DispatchThreadID)
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	color += inputTexture[tid.xy] * weight.x;

	color += inputTexture[tid.xy - off1] * weight.y;
	color += inputTexture[tid.xy - off2] * weight.z;
	color += inputTexture[tid.xy - off3] * weight.w;

	color += inputTexture[tid.xy + off1] * weight.y;
	color += inputTexture[tid.xy + off2] * weight.z;
	color += inputTexture[tid.xy + off3] * weight.w;

	color.w = 1.0f;
	outputTexture[tid.xy] = color;
}