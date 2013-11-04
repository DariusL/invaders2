#pragma once

#pragma warning(disable : 4005)

#include "includes.h"

#include "Utils.h"
#include "IInstanceShader.h"

using namespace std;

class ColorInstancedShader : public IInstanceShader
{
public:
	ColorInstancedShader(void);
	~ColorInstancedShader(void);

	virtual bool Init(ComPtr<ID3D11Device> device);
	virtual void SetShaderParameters(const RenderParams &params);
	virtual void RenderShader(ComPtr<ID3D11DeviceContext>, int indexCount, int instanceCount);
	//because fuck the linker
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix){};
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount){};

protected:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

private:
	ComPtr<ID3D11Buffer> matrixBuffer;
};