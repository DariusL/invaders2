#pragma once

#pragma warning(disable : 4005)

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <memory>
#include "Utils.h"
#include "Globals.h"

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
	unique_ptr<ID3D11VertexShader, COMDeleter> vertexShader;
	unique_ptr<ID3D11InputLayout, COMDeleter> layout;
	unique_ptr<ID3D11PixelShader, COMDeleter> pixelShader;
	unique_ptr<ID3D11Buffer, COMDeleter> matrixBuffer;
	unique_ptr<ID3D11Buffer, COMDeleter> lightingBuffer;
};