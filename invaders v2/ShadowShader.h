#pragma once
#include "TextureShader.h"
class ShadowShader : public TextureShader
{
public:
	ShadowShader(wstring vs, wstring ps) :TextureShader(vs, ps){}
	~ShadowShader(){}

	virtual void SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures);

protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual void InitializeSampler(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11SamplerState> compareSamplerState;
	ComPtr<ID3D11Buffer> pixelLightBuffer;
	ComPtr<ID3D11Buffer> vertexLightBuffer;
	ComPtr<ID3D11Buffer> inverseMatrixBuffer;

	struct ShadowLightBufferType
	{
		DirectX::XMFLOAT4X4 lightView;
		DirectX::XMFLOAT4X4 lightProject;
		DirectX::XMFLOAT3 lightPos;
		float padding;
	};

	struct PixelLightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT4 ambient;
	};
};

