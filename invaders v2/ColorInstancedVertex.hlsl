cbuffer TransMatrix : register(b0)
{
	matrix view;
	matrix projection;
	matrix scale;
};

struct VertexInputType
{
    float4 position : POSITION0;
	float4 instancePos : POSITION1;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInputType ColorInstancedVertexShader(VertexInputType input)
{
    PixelInputType output;

	output.position = mul(scale, input.position) + input.instancePos;
	output.position.w = 1.0f;
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
    
    output.color = input.color;
    
    return output;
}