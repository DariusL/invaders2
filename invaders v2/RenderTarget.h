#pragma once
#include "includes.h"
#include "Globals.h"
#include "Texture.h"
using namespace Microsoft::WRL;
class RenderTarget
{
	float clear[4];
	int width, height;

	Texture renderTarget;
	ComPtr<ID3D11DepthStencilView> depthStencilView;
	ComPtr<ID3D11DepthStencilState> depthStencilState;
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	D3D11_VIEWPORT viewport;
public:
	RenderTarget(ID3D11Device *device, int width, int height);
	RenderTarget(RenderTarget &&other);
	~RenderTarget(void);

	RenderTarget(RenderTarget&) = delete;
	RenderTarget &operator=(RenderTarget&) = delete;

	void SetRenderTarget(ID3D11DeviceContext *context);
	void ClearTarget(ID3D11DeviceContext *context);

	ID3D11ShaderResourceView *GetRenderedTexture(){return renderTarget.GetSRV();}
	ID3D11UnorderedAccessView *GetUnorderedAccess(){ return renderTarget.GetUAV(); }
private:
	void Init(ID3D11Device *device);
};

