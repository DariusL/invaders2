cbuffer AmbientLighting : register(b0)
{
	float4 brightness;
}

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 ColorPixelShader(PixelInputType input) : SV_TARGET
{
	//input.position = input.position / 16.0f;
    //return float4(abs(tan(input.position.x)), abs(sin(input.position.y)), abs(cos(input.position.z)), 1.0f);
	return input.color * brightness;
}