#pragma once
#include "camera.h"
#include "IDrawableObject.h"
#include "TextureShader.h"

#include <memory>

using namespace std;

class FloatingCamera : public Camera, public IDrawableObject
{
	D3DXMATRIX moveMatrix;
	float clear[4];
	ITextureShader &shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
	D3DXVECTOR2 viewportSize;
	D3DXVECTOR2 screenPos;

	ComPtr<ID3D11Texture2D> renderTargetTexture;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11DepthStencilView> depthStencilView;
	ComPtr<ID3D11DepthStencilState> depthStencilState;
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	ComVector<ID3D11ShaderResourceView> shaderResourceView;
	D3D11_VIEWPORT viewport;
public:
	FloatingCamera(D3DXVECTOR2 viewportSize, D3DXVECTOR2 screenPos, TextureShader &shader);
	~FloatingCamera(void);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &renderParams);

	void SetRenderTarget(ComPtr<ID3D11DeviceContext> context);
	void ClearTarget(ComPtr<ID3D11DeviceContext> context);

private:
	bool InitBuffers(ComPtr<ID3D11Device> device);
	void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	bool Update(ComPtr<ID3D11DeviceContext> context);

	void InitRenderTarget(ComPtr<ID3D11Device> device);
};

