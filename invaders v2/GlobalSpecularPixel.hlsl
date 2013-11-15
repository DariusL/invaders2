cbuffer LightBuffer : register(b0)
{
    float4 lightColor;
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
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 reflection;
	float3 lightDir = -lightDirection;

	intensity = saturate(dot(lightDir, input.normal));
	reflection = normalize(2 * intensity * input.normal - lightDir);

	diffuse = saturate(intensity * lightColor);

	specular = pow(saturate(dot(input.cameraDir, reflection)), 15);

	return input.color * diffuse + brightness * input.color + specular * intensity;
}