#include "IShader.h"
#include "Utils.h"

#include <memory>

using namespace std;

bool IShader::InitializeShader(ComPtr<ID3D11Device> device, char* vsFilename, char* psFilename, const vector<D3D11_INPUT_ELEMENT_DESC> &inputLayout)
{
	unique_ptr<char> vBuffer;
	int vSize;
	if(!Utils::ReadFileToArray(vsFilename, vBuffer, vSize))
		return false;

	// Create the vertex shader from the buffer.
	Assert(device->CreateVertexShader(vBuffer.get(), vSize, NULL, &vertexShader));

	unique_ptr<char> pBuffer;
	int pSize;
	if(!Utils::ReadFileToArray(psFilename, pBuffer, pSize))
		return false;

	// Create the pixel shader from the buffer.
	Assert(device->CreatePixelShader(pBuffer.get(), pSize, NULL, &pixelShader));

	Assert(device->CreateInputLayout(&inputLayout[0], inputLayout.size(), vBuffer.get(), vSize, &layout));

	return true;
}