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
	float intensity;
	float4 diffuse;
	intensity = saturate(dot(-lightDirection, input.normal));
	diffuse = saturate(intensity * diffuseColor);
	return input.color * diffuse + brightness * input.color;
}