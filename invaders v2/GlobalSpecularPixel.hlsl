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
	float3 cameraDir : POSITION;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float intensity;

	float4 diffuse;
	float4 specular;

	float3 reflection;

	intensity = saturate(dot(-lightDirection, input.normal));
	reflection = normalize(2 * intensity * input.normal + lightDirection);

	diffuse = saturate(intensity * diffuseColor);
	specular = pow(saturate(dot(reflection, input.cameraDir)), 15);

	return input.color * diffuse + brightness * input.color + specular;
}