#pragma once
#include "pointdiffuseshader.h"
class PointSpecularShader : public PointDiffuseShader
{
public:
	PointSpecularShader(wstring vs, wstring ps):PointDiffuseShader(vs, ps){}
	virtual ~PointSpecularShader(void){}
	
	virtual void SetShaderParameters(RenderParams &params, const XMMATRIX &world);
protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

