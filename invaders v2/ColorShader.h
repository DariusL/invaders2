#pragma once

#pragma warning(disable : 4005)

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <memory>
#include "Utils.h"
#include "Globals.h"

using namespace std;

class ColorShader
{
public:
	ColorShader(void);
	~ColorShader(void);

	bool Init(ID3D11Device*);
	void SetShaderParameters(RenderParams, D3DXMATRIX);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	bool InitializeShader(ID3D11Device*, char*, char*);

private:
	unique_ptr<ID3D11VertexShader, COMDeleter> vertexShader;
	unique_ptr<ID3D11InputLayout, COMDeleter> layout;
	unique_ptr<ID3D11PixelShader, COMDeleter> pixelShader;
	unique_ptr<ID3D11Buffer, COMDeleter> matrixBuffer;
	unique_ptr<ID3D11Buffer, COMDeleter> lightingBuffer;

	static const int IND_MATRIX = 0;
	static const int IND_LIGHTING = 1;
};