cbuffer TransMatrix : register(b0)
{
	matrix view;
	matrix projection;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
};

struct VertexInputType
{
    float4 position : POSITION0;
	float4 color : COLOR;
    float3 normal : NORMAL;
	float4 instancePos : POSITION1;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
    
    input.position.w = 1.0f;

	output.position = input.position + input.instancePos;
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

    output.color = input.color;
	output.normal = normalize(input.normal);
    
    return output;
}