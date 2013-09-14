cbuffer TransMatrix : register(b0)
{
    matrix transform;
};

cbuffer CameraBuffer : register(b1)
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
    
    input.position.w = 1.0f;

	output.position = mul(input.position, transform);
    output.color = input.color;
	output.normal = normalize(input.normal);
	output.cameraDir = normalize(cameraPos.xyz - input.position.xyz);
    
    return output;
}