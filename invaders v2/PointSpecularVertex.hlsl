cbuffer TransMatrix : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer LightBuffer : register(b2)
{
	float4 lightPos;
};

cbuffer CameraBuffer : register(b3)
{
	float3 cameraPos;//kameros pozicija
	float padding;//papildomi duomenys iki 16B
};

//output
struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float3 cameraDir : POSITION0;//kameros kryptis nuo tasko
	float3 lightDir : POSITION1;//sviesos kryptis nuo tasko
};

//input
struct VertexInputType
{
    float4 position : POSITION;
	float4 color : COLOR;
    float3 normal : NORMAL;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	float4 worldPos;
    
    input.position.w = 1.0f;
	//virsunes padetis pasaulio erdveje
	worldPos = mul(input.position, world);

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

    output.color = input.color;
	output.normal = normalize(input.normal);
	output.cameraDir = normalize(cameraPos.xyz - worldPos.xyz);//kamera nuo virsunes
	output.lightDir = normalize(lightPos.xyz - worldPos.xyz);//sviesa nuo virsunes
    
    return output;
}