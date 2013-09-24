#pragma once
#include "globaldiffuseshader.h"
class GlobalSpecularShader : public GlobalDiffuseShader
{
public:
	GlobalSpecularShader(void);
	~GlobalSpecularShader(void);

	virtual bool Init(ComPtr<ID3D11Device> device);
	
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);

private:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

