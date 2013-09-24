#pragma once

#include "includes.h"

#include "Utils.h"
#include "IPosShader.h"

using namespace std;

class ColorShader : public IPositionShader
{
public:
	ColorShader(void);
	~ColorShader(void);

	bool Init(ComPtr<ID3D11Device>);
	void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);
	void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

protected:
	bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

private:
	ComPtr<ID3D11Buffer> matrixBuffer;
};