#pragma once
#include "globaldiffuseshader.h"
class GlobalSpecularShader : public GlobalDiffuseShader
{
public:
	GlobalSpecularShader(string vs, string ps):GlobalDiffuseShader(vs, ps){}
	~GlobalSpecularShader(void){}
	
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);

private:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

