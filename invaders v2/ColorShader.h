#pragma once

#pragma warning(disable : 4005)

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <memory>
#include "Utils.h"
#include "Globals.h"

using namespace Microsoft::WRL;
using namespace std;

class ColorShader
{
public:
	ColorShader(void);
	~ColorShader(void);

	bool Init(ComPtr<ID3D11Device>);
	void SetShaderParameters(RenderParams, D3DXMATRIX);
	void RenderShader(ComPtr<ID3D11DeviceContext>, int);

private:
	bool InitializeShader(ComPtr<ID3D11Device>, char*, char*);

private:
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11InputLayout> layout;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11Buffer> lightingBuffer;
};