cbuffer TransMatrix : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer CameraBuffer : register(b2)
{
	float3 cameraPos;
	float padding;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float3 cameraDir : POSITION;
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
	worldPos = mul(input.position, world);

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

    output.color = input.color;
	output.normal = normalize(input.normal);
	output.cameraDir = normalize(cameraPos.xyz - worldPos.xyz);
    
    return output;
}