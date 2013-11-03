#pragma once

#include "Globals.h"

using namespace Microsoft::WRL;
using namespace std;

class IShader
{
public:
	virtual bool Init(ComPtr<ID3D11Device> device) = 0;

protected:
	bool InitializeShader(ComPtr<ID3D11Device> device, char* vsFilename, char* psFilename, const vector<D3D11_INPUT_ELEMENT_DESC> &inputLayout);
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device) = 0;
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout() = 0;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> layout;
};