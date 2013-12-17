#pragma once
#include "HorizontalBlurShader.h"
class VerticalBlurShader : public HorizontalBlurShader
{
public:
	VerticalBlurShader(wstring vs, wstring ps) :HorizontalBlurShader(vs, ps){}
	virtual ~VerticalBlurShader(){}
protected:

	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
};

