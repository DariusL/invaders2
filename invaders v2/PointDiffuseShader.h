#pragma once
#include "IPosShader.h"
class PointDiffuseShader : public IPositionShader
{
public:
	PointDiffuseShader(wstring vs, wstring ps):IPositionShader(vs, ps){}
	~PointDiffuseShader(void){}

public:	
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);

protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

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

