#pragma once

#pragma warning(disable : 4005)

#include "includes.h"

#include "Utils.h"
#include "IInstanceShader.h"

using namespace std;

class ColorInstancedShader : public IInstanceShader
{
public:
	ColorInstancedShader(wstring vs, wstring ps) :IInstanceShader(vs, ps){}
	~ColorInstancedShader(void){}

	virtual void SetShaderParametersInstanced(const RenderParams &params);
	virtual void RenderShaderInstanced(ComPtr<ID3D11DeviceContext>, int indexCount, int instanceCount);

protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

private:
	ComPtr<ID3D11Buffer> matrixBuffer;
};