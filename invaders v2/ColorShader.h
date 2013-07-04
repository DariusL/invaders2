#pragma once

#pragma warning(disable : 4005)

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <fstream>
#include "Globals.h"

using namespace std;

class ColorShader
{
public:
	ColorShader(void);
	~ColorShader(void){}

	bool Init(ID3D11Device*, HWND);
	void Shutdown();
	void SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	bool InitializeShader(ID3D11Device*, HWND, char*, char*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

private:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	ID3D11Buffer* matrixBuffer;
};