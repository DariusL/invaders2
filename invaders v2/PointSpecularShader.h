#pragma once
#include "pointdiffuseshader.h"
class PointSpecularShader : public PointDiffuseShader
{
public:
	PointSpecularShader(string vs, string ps):PointDiffuseShader(vs, ps){}
	~PointSpecularShader(void){}
	
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);
protected:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

