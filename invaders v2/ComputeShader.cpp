#include "includes.h"
#include "ComputeShader.h"
#include "Utils.h"

const uint ComputeShader::groupX = 32;
const uint ComputeShader::groupY = 32;

void ComputeShader::Init(ComPtr<ID3D11Device> device)
{
	InitializeShader(device, cs);
	InitializeShaderBuffers(device);
}

void ComputeShader::InitializeShader(ComPtr<ID3D11Device> device, wstring cs)
{
	unique_ptr<char> buffer;
	UINT size;

	AssertBool(Utils::ReadFileToArray(cs, buffer, size), L"Could not read " + cs);

	// Create the vertex shader from the buffer.
	Assert(device->CreateComputeShader(buffer.get(), size, NULL, &shader));
}

void ComputeShader::SetShader(ComPtr<ID3D11DeviceContext> context)
{
	context->CSSetShader(shader.Get(), nullptr, 0);
}

void ComputeShader::SetShaderParameters(ComPtr<ID3D11DeviceContext> context, ComVector<ID3D11ShaderResourceView> textures)
{
	texturesSet = textures.size();
	for (uint i = 0; i < texturesSet; i++)
		context->CSSetShaderResources(i, 1, textures[i].GetAddressOf());
	SetShader(context);
}

void ComputeShader::Start(ComPtr<ID3D11DeviceContext> context, uint width, uint height)
{
	uint sizeX = width / groupX;
	if (width % groupX != 0)
		sizeX++;

	uint sizeY = height / groupY;
	if (height % groupY != 0)
		sizeY++;

	context->Dispatch(sizeX, sizeY, 1);
	for (uint i = 0; i < texturesSet; i++)
		context->CSSetShaderResources(i, 1, nullptr);
}