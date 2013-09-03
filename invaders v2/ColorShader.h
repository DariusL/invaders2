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

	bool Init(ID3D11Device*, HWND);
	void SetShaderParameters(RenderParams);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	bool InitializeShader(ID3D11Device*, HWND, char*, char*);
	void ShutdownShader();

private:
	ID3D11VertexShader* vertexShader;
	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer **constantBuffers;

	static const int IND_MATRIX = 0;
	static const int IND_LIGHTING = 1;
};