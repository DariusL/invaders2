cbuffer TransMatrix : register(b0)
{
    matrix transform;
};

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
    //output.position.x += sin(output.position.x);
	//output.position.y += cos(output.position.x);
    output.color = input.color;
    
    return output;
}