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

	virtual bool Init(ComPtr<ID3D11Device>);
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);

protected:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

private:
	ComPtr<ID3D11Buffer> matrixBuffer;
};