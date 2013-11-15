#include "includes.h"
#include "IShader.h"
#include "Utils.h"

using namespace std;

void IShader::Init(ComPtr<ID3D11Device> device)
{
	InitializeShader(device, vs, ps, GetInputLayout());
	InitializeShaderBuffers(device);
}

void IShader::InitializeShader(ComPtr<ID3D11Device> device, wstring vs, wstring ps, const vector<D3D11_INPUT_ELEMENT_DESC> &inputLayout)
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

	Assert(device->CreateInputLayout(&inputLayout[0], inputLayout.size(), vBuffer.get(), vSize, &layout));
}

void IShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));
}