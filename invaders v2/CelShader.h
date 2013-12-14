#pragma once
#include "TextureShader.h"
class CelShader : public TextureShader
{
public:
	CelShader(wstring vs, wstring ps) :TextureShader(vs, ps){}

protected:
	ComPtr<ID3D11Buffer> celBuffer;

	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	struct CelBuffer
	{
		DirectX::XMFLOAT3X3 kernelX;
		DirectX::XMFLOAT3X3 kernelY;
		float offset;
		DirectX::XMFLOAT3 xOffset;
		DirectX::XMFLOAT3 yOffset;
		DirectX::XMFLOAT3 padding;
	};
};

