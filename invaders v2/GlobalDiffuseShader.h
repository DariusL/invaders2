#pragma once
#include "iposshader.h"
#include "Utils.h"

class GlobalDiffuseShader : public IPositionShader
{
public:
	GlobalDiffuseShader(void);
	~GlobalDiffuseShader(void);

public:
	virtual bool Init(ComPtr<ID3D11Device> device);
	
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);

protected:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11Buffer> lightingBuffer;

	struct LightBufferType
	{
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR3 lightDir;
		float brightness;
	};
};

