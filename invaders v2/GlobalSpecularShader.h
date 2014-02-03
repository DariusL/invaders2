#pragma once
#include "globaldiffuseshader.h"
class GlobalSpecularShader : public GlobalDiffuseShader
{
public:
	GlobalSpecularShader(wstring vs, wstring ps) :GlobalDiffuseShader(vs, ps){}
	virtual ~GlobalSpecularShader(void){}
	
	virtual void SetShaderParameters(RenderParams &params, const XMMATRIX &world);

private:
	virtual void InitializeShaderBuffers(ID3D11Device *device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

