#pragma once 

#include "IShader.h"

class IInstanceShader : public IShader
{
public:
	virtual void SetShaderParameters(RenderParams params) = 0;
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount, int instanceCount) = 0;
};