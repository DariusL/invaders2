cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

struct PixelInputType
{
    float4 position : SV_POSITION;
};

float4 ColorPixelShader(PixelInputType input) : SV_TARGET
{
	//input.position = input.position / 16.0f;
    //return float4(abs(tan(input.position.x)), abs(sin(input.position.y)), abs(cos(input.position.z)), 1.0f);
	return color;
}