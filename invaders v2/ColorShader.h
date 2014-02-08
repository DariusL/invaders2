#pragma once

#include "includes.h"

#include "Utils.h"
#include "IPosShader.h"
#include "Buffer.h"

using namespace std;

class ColorShader : public IPositionShader
{
public:
	ColorShader(wstring vs, wstring ps):IPositionShader(vs, ps){}
	virtual ~ColorShader(void){}
	virtual void SetShaderParameters(const RenderParams &params, const XMMATRIX &world);
	virtual void SetShaderParameters(const RenderParams &params, const XMMATRIX &world, const e::XMFLOAT4 color);
protected:
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
	virtual void InitializeShaderBuffers(ID3D11Device *device);
	Buffer<e::XMFLOAT4> colorBuffer;
};