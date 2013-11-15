Texture2D normalMap;
SamplerState SampleType;

cbuffer LightBuffer : register(b0)
{
    float4 lightColor;
	float4 ambient;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
	float2 tex : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
	float3 cameraDir : POSITION0;
	float3 lightDir : POSITION1;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 bump = normalMap.Sample(SampleType, input.tex);
	bump = (bump * 2.0f) - 1.0f;

	float3 normal = normalize(input.normal + bump.x * input.tangent + bump.y * input.binormal);

	float intensity = saturate(dot(input.lightDir, normal));//difuzines intensyvumas
	float3 reflection = normalize(2 * intensity * normal - input.lightDir);//atspindzio vektorius

	float4 diffuse = saturate(intensity * lightColor);//divuzines spalva

	specular = pow(saturate(dot(input.cameraDir, reflection)), 15);//spindincios spalva spalva

	//galutine tasko spalva
	return input.color * diffuse + ambient * input.color + specular * intensity;
}