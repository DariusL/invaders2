#pragma once
#include "globaldiffuseshader.h"
class GlobalSpecularShader :
	public GlobalDiffuseShader
{
public:
	GlobalSpecularShader(void);
	~GlobalSpecularShader(void);

	bool Init(ComPtr<ID3D11Device> device);
	
	void SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix);

private:
	bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
};

