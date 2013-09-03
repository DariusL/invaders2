#include "ColorInstancedShader.h"


ColorInstancedShader::ColorInstancedShader(void)
{
}


ColorInstancedShader::~ColorInstancedShader(void)
{
}

bool ColorInstancedShader::Init(ID3D11Device* device, HWND hwnd)
{
	if(!InitializeShader(device, hwnd, "ColorInstancedVertex.cso", "ColorPixel.cso"))
		return false;
	return true;
}

bool ColorInstancedShader::InitializeShader(ID3D11Device* device, HWND hwnd, char* vsFilename, char* psFilename)
{
	unsigned int numElements = 3;
	D3D11_INPUT_ELEMENT_DESC *polygonLayout = new D3D11_INPUT_ELEMENT_DESC[numElements];
	D3D11_BUFFER_DESC matrixBufferDesc;

	unique_ptr<char> vBuffer;
	int vSize;
	Utils::ReadFileToArray(vsFilename, vBuffer, vSize);

	// Create the vertex shader from the buffer.
	if(FAILED(device->CreateVertexShader(vBuffer.get(), vSize, NULL, &vertexShader)))
		return false;

	unique_ptr<char> pBuffer;
	int pSize;
	Utils::ReadFileToArray(psFilename, pBuffer, pSize);

	// Create the pixel shader from the buffer.
	if(FAILED(device->CreatePixelShader(pBuffer.get(), pSize, NULL, &pixelShader)))
		return false;

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

	polygonLayout[2].SemanticName = "POSITION";
	polygonLayout[2].SemanticIndex = 1;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 1;
	polygonLayout[2].AlignedByteOffset = 0;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[2].InstanceDataStepRate = 1;

	// Create the vertex input layout.
	if(FAILED(device->CreateInputLayout(polygonLayout, numElements, vBuffer.get(), vSize, &layout)))
		return false;

	delete [] polygonLayout;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	if(FAILED(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer)))
		return false;

	return true;
}

void ColorInstancedShader::ShutdownShader()
{
	// Release the matrix constant buffer.
	if(matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}

	// Release the layout.
	if(layout)
	{
		layout->Release();
		layout = 0;
	}

	// Release the pixel shader.
	if(pixelShader)
	{
		pixelShader->Release();
		pixelShader = 0;
	}

	// Release the vertex shader.
	if(vertexShader)
	{
		vertexShader->Release();
		vertexShader = 0;
	}

	return;
}

void ColorInstancedShader::SetShaderParameters(RenderParams params)
{
	D3D11_MAPPED_SUBRESOURCE matrixRes, lightingRes;

	D3DXMatrixTranspose(&params.transMatrix, &params.transMatrix);

	params.context->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &matrixRes);

	memcpy(matrixRes.pData, &params.transMatrix, sizeof(D3DXMATRIX));

	params.context->Unmap(matrixBuffer, 0);

	// Finanly set the constant buffer in the vertex shader with the updated values.
	params.context->VSSetConstantBuffers(1, 1, &matrixBuffer);

	params.context->IASetInputLayout(layout);

	//set the shaders used for rendering
	params.context->VSSetShader(vertexShader, NULL, 0);
	params.context->PSSetShader(pixelShader, NULL, 0);
}

void ColorInstancedShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount, int instanceCount)
{
	//unleash the grafiks
	deviceContext->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
}