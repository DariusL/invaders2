#pragma once
#include "camera.h"
#include "IDrawableObject.h"
#include "ITextureShader.h"

#include <memory>

using namespace std;

class FloatingCamera : public Camera, public IDrawableObject
{
	D3DXMATRIX moveMatrix;
	shared_ptr<ITextureShader> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
	D3DXVECTOR2 viewportSize;
	D3DXVECTOR2 screenPos;

	ComPtr<ID3D11Texture2D> renderTargetTexture;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;
public:
	FloatingCamera(D3DXVECTOR2 viewportSize, D3DXVECTOR2 screenPos);
	~FloatingCamera(void);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(RenderParams renderParams);
	void Render(){Camera::Render();}

	ComPtr<ID3D11RenderTargetView> GetRenderTargetView(){return renderTargetView;}
private:
	bool InitBuffers(ComPtr<ID3D11Device> device);
	void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	bool Update(ComPtr<ID3D11DeviceContext> context);

	void InitRenderTarget(ComPtr<ID3D11Device> device);
};

