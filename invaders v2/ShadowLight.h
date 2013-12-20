#pragma once 
#include "includes.h"
#include "Light.h"
#include "Camera.h"

class ShadowLight : public Light
{
public:
	ShadowLight(ComPtr<ID3D11Device> device, XMFLOAT3 pos, XMFLOAT4 color, ColorModel &model, ColorShader &shader, int width, int height);

	void SetRenderTarget(ComPtr<ID3D11DeviceContext> context);
	void ClearTarget(ComPtr<ID3D11DeviceContext> context);

	ComPtr<ID3D11ShaderResourceView> GetRenderedTexture(){ return shaderResourceView; }
	XMMATRIX GetViewMatrix(){ return XMLoadFloat4x4(&view); }
	XMMATRIX GetProjectionMatrix(){ return XMLoadFloat4x4(&projection); }
	void Prepare(RenderParams &params);
protected:
	int width, height;
	ComPtr<ID3D11DepthStencilView> depthStencilView;
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	D3D11_VIEWPORT viewport;

	XMFLOAT4X4 view, projection;
private:
	void Init(ComPtr<ID3D11Device> device);
};