#pragma once
#include "pointdiffuseshader.h"
class PointSpecularShader : public PointDiffuseShader
{
public:
	PointSpecularShader(wstring vs, wstring ps):PointDiffuseShader(vs, ps){}
	~PointSpecularShader(void){}
	
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);
protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

