cbuffer LightBuffer
{
    float4 diffuseColor;
    float3 lightDirection;
	float brightness;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 color : COLOR;
    float3 normal : NORMAL;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 diffuse;
	diffuse = saturate(dot(-lightDirection, input.normal));
	diffuse.w = 1.0f;
	return diffuse * diffuseColor + brightness * input.color;
}