#pragma once

#include "includes.h"

#include "Utils.h"
#include "IInstanceShader.h"

class ColorInstancedShader : public IInstanceShader
{
public:
	ColorInstancedShader(e::wstring vs, e::wstring ps) :IInstanceShader(vs, ps){}
	virtual ~ColorInstancedShader(void){}
	virtual void SetShaderParametersInstanced(const RenderParams &params, e::XMFLOAT4 color);
	virtual void SetShaderParametersInstanced(const RenderParams &params);
	virtual void InitializeShaderBuffers(ID3D11Device *device);
protected:
	virtual e::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
	Buffer<e::XMFLOAT4> colorBuffer;
};