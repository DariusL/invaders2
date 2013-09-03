cbuffer TransMatrix : register(cb1)
{
    matrix transform;
};

cbuffer MoveMatrix : register(cb0)
{
	matrix move;
}

struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    input.position.w = 1.0f;

	output.position = mul(input.position, move);
	output.position = mul(output.position, transform);
    
    output.color = input.color;
    
    return output;
}