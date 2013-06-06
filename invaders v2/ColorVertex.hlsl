cbuffer TransMatrix
{
    matrix transform;
};

cbuffer MoveMatrix
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

    output.position = mul(input.position, transform);
	//output.position = mul(output.position, move);
    
    output.color = input.color;
    
    return output;
}