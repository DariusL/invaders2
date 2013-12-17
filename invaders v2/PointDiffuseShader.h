#pragma once
#include "IPosShader.h"
class PointDiffuseShader : public IPositionShader
{
public:
	PointDiffuseShader(wstring vs, wstring ps):IPositionShader(vs, ps){}
	virtual ~PointDiffuseShader(void){}

public:	
	virtual void SetShaderParameters(RenderParams &params, const XMMATRIX &world);

protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11Buffer> pixelLightBuffer;
	ComPtr<ID3D11Buffer> vertexLightBuffer;

	struct PixelLightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT4 ambient;
	};

	struct VertexLightBufferType
	{
		XMFLOAT4 lightPos;
	};
};

