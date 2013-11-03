cbuffer TransMatrix : register(b0)
{
    matrix transform;
	matrix move;
};

cbuffer CameraBuffer : register(b2)
{
	float3 cameraPos;
	float padding;
};

cbuffer ReflectionBuffer : register(b3)
{
    matrix reflectionTransform;
	matrix refractionTransform;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 reflectionMapPos : TEXCOORD1;
	float4 refractionMapPos : TEXCOORD2;
	float3 cameraDir : POSITION0;
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	float4 worldPos;
    
    input.position.w = 1.0f;
	worldPos = mul(input.position, move);

	output.position = mul(input.position, transform);
	output.tex = input.tex;

	output.cameraDir = normalize(cameraPos.xyz - worldPos.xyz);
	output.reflectionMapPos = mul(input.position, reflectionTransform);
	output.refractionMapPos = mul(input.position, refractionTransform);
    
    return output;
}