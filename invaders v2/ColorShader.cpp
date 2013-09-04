#include "ColorShader.h"


ColorShader::ColorShader()
{
	vertexShader = 0;
	pixelShader = 0;
	layout = 0;
}

ColorShader::~ColorShader()
{
}

bool ColorShader::Init(ID3D11Device* device)
{
	if(!InitializeShader(device, "ColorVertex.cso", "ColorPixel.cso"))
		return false;
	return true;
}

bool ColorShader::InitializeShader(ID3D11Device* device, char* vsFilename, char* psFilename)
{
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightingBufferDesc;
	ID3D11Buffer *bMatrix, *bLighting;
	ID3D11VertexShader *sVertex;
	ID3D11PixelShader *sPixel;
	ID3D11InputLayout *inputLayout;

	unique_ptr<char> vBuffer;
	int vSize;
	Utils::ReadFileToArray(vsFilename, vBuffer, vSize);

	// Create the vertex shader from the buffer.
	if(FAILED(device->CreateVertexShader(vBuffer.get(), vSize, NULL, &sVertex)))
		return false;

	vertexShader = unique_ptr<ID3D11VertexShader, COMDeleter>(sVertex);

	unique_ptr<char> pBuffer;
	int pSize;
	Utils::ReadFileToArray(psFilename, pBuffer, pSize);

	// Create the pixel shader from the buffer.
	if(FAILED(device->CreatePixelShader(pBuffer.get(), pSize, NULL, &sPixel)))
		return false;

	pixelShader = unique_ptr<ID3D11PixelShader, COMDeleter>(sPixel);

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	if(FAILED(device->CreateInputLayout(polygonLayout, numElements, vBuffer.get(), vSize, &inputLayout)))
		return false;

	layout = unique_ptr<ID3D11InputLayout, COMDeleter>(inputLayout);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	if(FAILED(device->CreateBuffer(&matrixBufferDesc, NULL, &bMatrix)))
		return false;

	matrixBuffer = unique_ptr<ID3D11Buffer, COMDeleter>(bMatrix);

	lightingBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightingBufferDesc.ByteWidth = sizeof(D3DXVECTOR4);
	lightingBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightingBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightingBufferDesc.MiscFlags = 0;
	lightingBufferDesc.StructureByteStride = 0;

	if(FAILED(device->CreateBuffer(&lightingBufferDesc, NULL, &bLighting)))
		return false;

	lightingBuffer = unique_ptr<ID3D11Buffer, COMDeleter>(bLighting);

	return true;
}

void ColorShader::SetShaderParameters(RenderParams params, D3DXMATRIX moveMatrix)
{
	D3D11_MAPPED_SUBRESOURCE matrixRes, lightingRes;
	D3DXVECTOR4 brightnessVector = D3DXVECTOR4(params.brightness, params.brightness, params.brightness, 1.0f);
	ID3D11Buffer *bMatrix = matrixBuffer.get();
	ID3D11Buffer *bLighting = lightingBuffer.get();

	params.transMatrix = moveMatrix * params.transMatrix;

	D3DXMatrixTranspose(&params.transMatrix, &params.transMatrix);

	params.context->Map(matrixBuffer.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &matrixRes);

	memcpy(matrixRes.pData, &params.transMatrix, sizeof(D3DXMATRIX));

	params.context->Unmap(matrixBuffer.get(), 0);

	params.context->Map(lightingBuffer.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &lightingRes);

	memcpy(lightingRes.pData, &brightnessVector, sizeof(D3DXVECTOR4));

	params.context->Unmap(lightingBuffer.get(), 0);

	params.context->VSSetConstantBuffers(0, 1, &bMatrix);
	params.context->PSSetConstantBuffers(0, 1, &bLighting);

	params.context->IASetInputLayout(layout.get());

	params.context->VSSetShader(vertexShader.get(), NULL, 0);
	params.context->PSSetShader(pixelShader.get(), NULL, 0);
}

void ColorShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	//unleash the grafiks
	deviceContext->DrawIndexed(indexCount, 0, 0);
 }