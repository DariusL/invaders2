#pragma once 
#include "includes.h"
#include "Light.h"
#include "Camera.h"

class ShadowLight : public Light
{
public:
	ShadowLight(XMFLOAT3 pos, XMFLOAT4 color, ColorModel &model, ColorShader &shader, int width, int height);

	void Init(ComPtr<ID3D11Device> device);

	void SetRenderTarget(ComPtr<ID3D11DeviceContext> context);
	void ClearTarget(ComPtr<ID3D11DeviceContext> context);

	ComPtr<ID3D11ShaderResourceView> GetRenderedTexture(){ return shaderResourceView; }
	ComPtr<ID3D11ShaderResourceView> GetOtherTexture(){ return renderTargetTextureView; }
	XMMATRIX GetViewMatrix(){ return XMLoadFloat4x4(&view); }
	XMMATRIX GetProjectionMatrix(){ return XMLoadFloat4x4(&projection); }
protected:
	int width, height;
	ComPtr<ID3D11DepthStencilView> depthStencilView;
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11ShaderResourceView> renderTargetTextureView;
	ComPtr<ID3D11Texture2D> renderTargetTexure;
	D3D11_VIEWPORT viewport;

	XMFLOAT4X4 view, projection;
};