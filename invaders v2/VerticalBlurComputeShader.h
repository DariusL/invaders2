#pragma once
#include "HorizontalBlurComputeShader.h"
class VerticalBlurComputeShader : public HorizontalBlurComputeShader
{
public:
	VerticalBlurComputeShader(wstring cs) : HorizontalBlurComputeShader(cs){}
	virtual ~VerticalBlurComputeShader(){}
protected:
	virtual void InitializeShaderBuffers(ID3D11Device *device);
};

