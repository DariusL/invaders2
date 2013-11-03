#pragma once
#include "includes.h"
#include "Globals.h"
using namespace Microsoft::WRL;
class RenderTarget
{
	float clear[4];
	int width, height;

	ComPtr<ID3D11Texture2D> renderTargetTexture;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11DepthStencilView> depthStencilView;
	ComPtr<ID3D11DepthStencilState> depthStencilState;
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	D3D11_VIEWPORT viewport;
public:
	RenderTarget(int width, int height);
	~RenderTarget(void);

	bool Init(ComPtr<ID3D11Device> device);

	void SetRenderTarget(ComPtr<ID3D11DeviceContext> context);
	void ClearTarget(ComPtr<ID3D11DeviceContext> context);

	ComPtr<ID3D11ShaderResourceView> GetRenderedTexture(){return shaderResourceView;}
};

