#include "includes.h"
#include "ComputeShader.h"
#include "Utils.h"

const uint ComputeShader::groupX = 32;
const uint ComputeShader::groupY = 32;

void ComputeShader::Init(ID3D11Device *device)
{
	InitializeShader(device, cs);
	InitializeShaderBuffers(device);
}

void ComputeShader::InitializeShader(ID3D11Device *device, e::wstring cs)
{
	using namespace e;
	e::unique_ptr<char> buffer;
	UINT size;

	AssertBool(Utils::ReadFileToArray(cs, buffer, size), L"Could not read " + cs);

	Assert(device->CreateComputeShader(buffer.get(), size, NULL, &shader));
}

void ComputeShader::SetShaderParameters(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output)
{
	context->CSSetShaderResources(0, 1, &input);
	context->CSSetUnorderedAccessViews(0, 1, &output, 0);
	context->CSSetShader(shader.Get(), nullptr, 0);
}

void ComputeShader::Start(ID3D11DeviceContext *context, uint width, uint height)
{
	uint sizeX = width / groupX;
	if (width % groupX != 0)
		sizeX++;

	uint sizeY = height / groupY;
	if (height % groupY != 0)
		sizeY++;

	context->Dispatch(sizeX, sizeY, 1);

	context->CSSetShaderResources(0, 1, nullResourceView.GetAddressOf());
	context->CSSetUnorderedAccessViews(0, 1, nullUnorderedView.GetAddressOf(), 0);
}