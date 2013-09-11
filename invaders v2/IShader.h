#pragma once

#include <wrl\client.h>
#include "Globals.h"

using namespace Microsoft::WRL;

class IShader
{
public:
	virtual bool Init(ComPtr<ID3D11Device> device) = 0;

protected:
	bool InitializeShader(ComPtr<ID3D11Device> device, char* vsFilename, char* psFilename, D3D11_INPUT_ELEMENT_DESC *polygonLayout, int layoutCount);
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device) = 0;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> layout;
};