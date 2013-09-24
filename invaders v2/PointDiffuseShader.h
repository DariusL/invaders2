#pragma once
#include "IPosShader.h"
class PointDiffuseShader : public IPositionShader
{
public:
	PointDiffuseShader(void);
	~PointDiffuseShader(void);

public:
	virtual bool Init(ComPtr<ID3D11Device> device);
	
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

protected:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11Buffer> pixelLightBuffer;
	ComPtr<ID3D11Buffer> vertexLightBuffer;

	struct PixelLightBufferType
	{
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR4 ambient;
	};

	struct VertexLightBufferType
	{
		D3DXVECTOR4 lightPos;
	};
};

