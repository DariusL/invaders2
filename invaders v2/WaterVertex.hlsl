cbuffer TransMatrix : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer ClipBuffer : register(b1)
{
	float4 clip;
}

cbuffer CameraBuffer : register(b3)
{
	float3 cameraPos;
	float padding;
};

cbuffer ReflectionBuffer : register(b2)
{
	matrix reflectView;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 reflectionPos : TEXCOORD1;
	float4 refractionPos : TEXCOORD2;
	float3 cameraDir : POSITION0;
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD;
};

[clipplanes(clip)]
PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	float4 worldPos;
    
    input.position.w = 1.0f;
	worldPos = mul(input.position, world);

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.tex = input.tex;

	output.cameraDir = normalize(cameraPos.xyz - worldPos.xyz);

	output.reflectionPos = mul(input.position, world);
	output.reflectionPos = mul(output.reflectionPos, reflectView);
	output.reflectionPos = mul(output.reflectionPos, projection);

	output.refractionPos = output.position;
    
    return output;
}