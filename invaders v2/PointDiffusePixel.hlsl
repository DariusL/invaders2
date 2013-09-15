cbuffer LightBuffer : register(b0)
{
    float4 diffuseColor;
	float4 ambient;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float3 lightDir : POSITION0;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float intensity;
	float4 diffuse;

	intensity = saturate(dot(input.lightDir, input.normal));
	diffuse = saturate(intensity * diffuseColor);

	return input.color * diffuse + ambient * input.color;
}