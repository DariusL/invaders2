#pragma once
#include "globaldiffuseshader.h"
class GlobalSpecularShader : public GlobalDiffuseShader
{
public:
	GlobalSpecularShader(e::wstring vs, e::wstring ps) :GlobalDiffuseShader(vs, ps){}
	virtual ~GlobalSpecularShader(void){}
	
	virtual void SetShaderParameters(const RenderParams &params, const e::XMMATRIX &world);

private:
	virtual void InitializeShaderBuffers(ID3D11Device *device);

	Buffer<e::XMFLOAT4> cameraBuffer;
};

