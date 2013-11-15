cbuffer LightBuffer : register(b0)
{
    float4 lightColor;//difuzines, spindincios sviesos spalva
	float4 ambient;//fonines spalva, intensyvumas
};

//input
struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float3 lightDir : POSITION0;//sviesos kryptis nuo tasko
};

float4 main(PixelInputType input) : SV_TARGET
{
	float intensity;
	float4 diffuse;

	//difuzinis intensyvumas
	intensity = saturate(dot(input.lightDir, input.normal));
	//galutine difuzine spalva
	diffuse = saturate(intensity * lightColor);

	return input.color * diffuse + ambient * input.color;
}