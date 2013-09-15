cbuffer LightBuffer : register(b0)
{
    float4 lightColor;
	float4 ambient;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float3 cameraDir : POSITION0;
	float3 lightDir : POSITION1;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float intensity;

	float4 diffuse;
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 reflection;

	intensity = saturate(dot(input.lightDir, input.normal));
	reflection = normalize(2 * intensity * input.normal - input.lightDir);

	diffuse = saturate(intensity * lightColor);
	//if(intensity > 0.01f)
	//{
		specular = pow(saturate(dot(input.cameraDir, reflection)), 15);
	//}

	return input.color * diffuse + ambient * input.color + specular;
}