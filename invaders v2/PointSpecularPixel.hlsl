cbuffer LightBuffer : register(b0)
{
    float4 lightColor;
	float4 ambient;
};

//input
struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float3 cameraDir : POSITION0;//kameros kryptis nuo tasko
	float3 lightDir : POSITION1;//sviesos kryptis nuo tasko
};

float4 main(PixelInputType input) : SV_TARGET
{
	float intensity;

	float4 diffuse;
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float3 reflection;

	intensity = saturate(dot(input.lightDir, input.normal));//difuzines intensyvumas
	reflection = normalize(2 * intensity * input.normal - input.lightDir);//atspindzio vektorius

	diffuse = saturate(intensity * lightColor);//divuzines spalva

	specular = pow(saturate(dot(input.cameraDir, reflection)), 15);//spindincios spalva spalva

	//galutine tasko spalva
	return input.color * diffuse + ambient * input.color + specular * intensity;
}