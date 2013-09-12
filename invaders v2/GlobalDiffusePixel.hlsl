cbuffer LightBuffer : register(b0)
{
    float4 diffuseColor;
    float3 lightDirection;
	float brightness;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float diffuse;
	diffuse = saturate(dot(-lightDirection, input.normal));
	return diffuse * diffuseColor + brightness * input.color;
}