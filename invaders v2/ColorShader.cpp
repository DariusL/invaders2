#include "ColorShader.h"


ColorShader::ColorShader()
{
	vertexShader = 0;
	pixelShader = 0;
	layout = 0;
	matrixBuffer = 0;
}

bool ColorShader::Init(ID3D11Device* device, HWND hwnd)
{
	if(!InitializeShader(device, hwnd, "..\\Debug\\ColorVertex.cso", "..\\Debug\\ColorPixel.cso"))
		return false;
	return true;
}

void ColorShader::Shutdown()
{
	ShutdownShader();
}

bool ColorShader::InitializeShader(ID3D11Device* device, HWND hwnd, char* vsFilename, char* psFilename)
{
	ID3D10Blob* errorMessage;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	errorMessage = NULL;
	
	// Compile the vertex shader code.
	/*if(FAILED(D3DX11CompileFromFile(vsFilename, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
				       &vertexShaderBuffer, &errorMessage, NULL)))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);

		return false;
	}

	// Compile the pixel shader code.
	if(FAILED(D3DX11CompileFromFile(psFilename, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
				       &pixelShaderBuffer, &errorMessage, NULL)))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		// If there was  nothing in the error message then it simply could not find the file itself.
		else
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);

		return false;
	}*/

	ifstream stream;
	stream.open(vsFilename, std::ifstream::binary | std::ifstream::in);
	stream.seekg(0, stream.end);
	int vSize = stream.tellg();
	stream.seekg(0, stream.beg);
	char *vBuffer = new char[vSize];
	stream.read(vBuffer, vSize);
	stream.close();

	// Create the vertex shader from the buffer.
	if(FAILED(device->CreateVertexShader(vBuffer, vSize, NULL, &vertexShader)))
		return false;

	stream.open(psFilename, ios::binary);
	stream.seekg(0, stream.end);
	int pSize = stream.tellg();
	stream.seekg(0, stream.beg);
	char *pBuffer = new char[pSize];
	stream.read(pBuffer, pSize);
	stream.close();

	// Create the pixel shader from the buffer.
	if(FAILED(device->CreatePixelShader(pBuffer, pSize, NULL, &pixelShader)))
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

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	if(FAILED(device->CreateInputLayout(polygonLayout, numElements, vBuffer, vSize, &layout)))
		return false;

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	delete [] vBuffer;
	delete [] pBuffer;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
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

void ColorShader::ShutdownShader()
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

void ColorShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	ofstream fout;

	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.

	fout << compileErrors;

	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);
}

void ColorShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX transMatrix)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	D3DXMatrixTranspose(&transMatrix, &transMatrix);

	deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, &transMatrix, sizeof(D3DXMATRIX));

	deviceContext->Unmap(matrixBuffer, 0);

	// Finanly set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(0, 1, &matrixBuffer);

	deviceContext->IASetInputLayout(layout);

	//set the shaders used for rendering
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);
}

void ColorShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	//unleash the grafiks
	deviceContext->DrawIndexed(indexCount, 0, 0);
}