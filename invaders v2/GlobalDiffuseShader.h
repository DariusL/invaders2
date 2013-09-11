#pragma once
#include "iposshader.h"
class GlobalDiffuseShader : public IPositionShader
{
public:
	GlobalDiffuseShader(void);
	~GlobalDiffuseShader(void);

public:
	bool Init(ComPtr<ID3D11Device> device);
	
	void SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix);
	void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

private:
	bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11Buffer> lightingBuffer;
};

