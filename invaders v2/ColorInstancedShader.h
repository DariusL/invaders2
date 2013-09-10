#pragma once

#pragma warning(disable : 4005)

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <memory>

#include "Utils.h"
#include "IInstanceShader.h"

using namespace std;

class ColorInstancedShader : public IInstanceShader
{
public:
	ColorInstancedShader(void);
	~ColorInstancedShader(void);

	bool Init(ComPtr<ID3D11Device>);
	void SetShaderParameters(RenderParams);
	void RenderShader(ComPtr<ID3D11DeviceContext>, int indexCount, int instanceCount);

private:
	bool InitializeShader(ComPtr<ID3D11Device> device, char* vsFilename, char* psFilename);

private:
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11InputLayout> layout;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11Buffer> lightingBuffer;
};