cbuffer TransMatrix : register(b0)
{
    matrix transform;
	matrix move;
};

cbuffer LightBuffer : register(b1)
{
	float4 lightPos;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float3 lightDir : POSITION0;
};

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
	worldPos = mul(input.position, move);

	output.position = mul(input.position, transform);
    output.color = input.color;
	output.normal = normalize(input.normal);
	output.lightDir = normalize(lightPos.xyz - worldPos.xyz);
    
    return output;
}