#pragma once

#pragma warning(disable : 4005)

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <memory>

#include "Utils.h"
#include "IPosShader.h"

using namespace std;

class ColorShader : public IPositionShader
{
public:
	ColorShader(void);
	~ColorShader(void);

	bool Init(ComPtr<ID3D11Device>);
	void SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix);
	void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

private:
	bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

private:
	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11Buffer> lightingBuffer;
};