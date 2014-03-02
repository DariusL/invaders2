#pragma once

#include "includes.h"

#include "Utils.h"
#include "IPosShader.h"
#include "Buffer.h"

class ColorShader : public IPositionShader
{
public:
	ColorShader(e::wstring vs, e::wstring ps) :IPositionShader(vs, ps){}
	virtual ~ColorShader(void){}
	virtual void SetShaderParameters(const RenderParams &params, const e::XMMATRIX &world);
	virtual void SetShaderParameters(const RenderParams &params, const e::XMMATRIX &world, const e::XMFLOAT4 color);
protected:
	virtual e::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
	virtual void InitializeShaderBuffers(ID3D11Device *device);
	Buffer<e::XMFLOAT4> colorBuffer;
};