cbuffer LightBuffer : register(b0)
{
    float4 diffuseColor;
    float3 lightDirection;
	float brightness;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 color : COLOR;
    float4 normal : NORMAL;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 diffuse;
	float4 dir;
	dir = float4(lightDirection, 1.0f);
	diffuse = saturate(dot(-dir, input.normal));
	diffuse.w = 1.0f;
	return diffuse * diffuseColor + brightness * input.color;
}