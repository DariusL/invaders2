#pragma once
#include "pointdiffuseshader.h"
class PointSpecularShader : public PointDiffuseShader
{
public:
	PointSpecularShader(void);
	~PointSpecularShader(void);

	virtual bool Init(ComPtr<ID3D11Device> device);
	
	virtual void SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix);

private:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

