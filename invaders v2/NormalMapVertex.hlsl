cbuffer TransMatrix : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer LightBuffer : register(b1)
{
	float4 lightPos;
};

cbuffer CameraBuffer : register(b2)
{
	float3 cameraPos;//kameros pozicija
	float padding;//papildomi duomenys iki 16B
};

struct VertexInputType
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
	float2 tex : TEXCOORD;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
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

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	float4 worldPos;
    
    input.position.w = 1.0f;
	worldPos = mul(input.position, world);

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

    output.color = input.color;
	output.tex = input.tex;

	output.cameraDir = normalize(cameraPos.xyz - worldPos.xyz);
	output.lightDir = normalize(lightPos.xyz - worldPos.xyz);

	output.normal = normalize(input.normal);
	output.tangent = normalize(input.tangent);
	output.binormal = normalize(input.binormal);
    
    return output;
}