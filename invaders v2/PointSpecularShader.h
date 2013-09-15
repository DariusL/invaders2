#pragma once
#include "pointdiffuseshader.h"
class PointSpecularShader : public PointDiffuseShader
{
public:
	PointSpecularShader(void);
	~PointSpecularShader(void);

		bool Init(ComPtr<ID3D11Device> device);
	
	void SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix);

private:
	bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

