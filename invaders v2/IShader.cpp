#include "includes.h"
#include "IShader.h"
#include "Utils.h"

using namespace std;

void IShader::Init(ID3D11Device *device)
{
	InitializeShader(device, vs, ps, GetInputLayout());
	InitializeShaderBuffers(device);
}

void IShader::InitializeShader(ID3D11Device *device, wstring vs, wstring ps, const vector<D3D11_INPUT_ELEMENT_DESC> &inputLayout)
{
	unique_ptr<char> vBuffer;
	UINT vSize;

	AssertBool(Utils::ReadFileToArray(vs, vBuffer, vSize), L"Could not read " + vs);

	// Create the vertex shader from the buffer.
	Assert(device->CreateVertexShader(vBuffer.get(), vSize, NULL, &vertexShader));

	unique_ptr<char> pBuffer;
	UINT pSize;
	AssertBool(Utils::ReadFileToArray(ps, pBuffer, pSize), L"Could not read " + ps);

	// Create the pixel shader from the buffer.
	Assert(device->CreatePixelShader(pBuffer.get(), pSize, NULL, &pixelShader));

	Assert(device->CreateInputLayout(inputLayout.data(), inputLayout.size(), vBuffer.get(), vSize, &layout));
}

void IShader::SetShader(RenderParams &params)
{
	params.context->PSSetShader(pixelShader.Get(), NULL, 0);
		
	params.context->VSSetShader(vertexShader.Get(), NULL, 0);
	params.context->IASetInputLayout(layout.Get());
	params.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}