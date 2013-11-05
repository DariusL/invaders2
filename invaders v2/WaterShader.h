#pragma once
#include "textureshader.h"
#include "includes.h"
using namespace std;
class WaterShader : public TextureShader
{
public:
	WaterShader(string vs, string ps):TextureShader(vs, ps){}
	~WaterShader(void){}

public:
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix, vector<ComPtr<ID3D11ShaderResourceView>> textures);
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);
protected:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
	ComPtr<ID3D11Buffer> waterBuffer;
	ComPtr<ID3D11Buffer> reflectionBuffer;
};