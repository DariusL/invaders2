cbuffer TransMatrix : register(b0)
{
    matrix transform;
	matrix move;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
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
    
    return output;
}