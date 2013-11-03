#pragma once
#include "textureshader.h"
#include "includes.h"
using namespace std;
class WaterShader : public TextureShader
{
public:
	WaterShader(void);
	~WaterShader(void);

public:
	virtual bool Init(ComPtr<ID3D11Device> device);
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix, vector<ComPtr<ID3D11ShaderResourceView>> textures);
protected:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
	ComPtr<ID3D11Buffer> waterBuffer;
	ComPtr<ID3D11Buffer> reflectionBuffer;
};