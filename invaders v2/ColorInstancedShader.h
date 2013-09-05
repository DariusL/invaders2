#pragma once

#pragma warning(disable : 4005)

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <memory>
#include <wrl\client.h>
#include "Utils.h"
#include "Globals.h"

using namespace std;
using namespace Microsoft::WRL;

class ColorInstancedShader
{
public:
	ColorInstancedShader(void);
	~ColorInstancedShader(void);

	bool Init(ID3D11Device*);
	void SetShaderParameters(RenderParams);
	void RenderShader(ID3D11DeviceContext*, int indexCount, int instanceCount);

private:
	bool InitializeShader(ID3D11Device*, char*, char*);

private:
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11InputLayout> layout;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11Buffer> lightingBuffer;
};