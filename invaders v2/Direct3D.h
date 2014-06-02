#pragma once

#include "includes.h"
#include "Utils.h"

class Direct3D
{
public:
	Direct3D(int width, int height, bool vsync, HWND whandle, bool fullscreen, float screendepth, float screennear);
	~Direct3D(void);

	void ClearRenderTarget();
	void Present();

	static ID3D11Device *GetDevice(){return staticDevice;}
	static ID3D11DeviceContext *GetDeviceContext(){return staticContext;}

	e::XMMATRIX GetProjectionMatrix(){ return XMLoadFloat4x4(&projectionMatrix); }
	e::XMMATRIX GetOrthoMatrix(){ return XMLoadFloat4x4(&orthoMatrix); }

	ID3D11UnorderedAccessView *GetBackBufferUnorderedAccess(){ return backBufferAccess.Get(); }

	void GetVideoCardInfo(char* name, int& memory){strcpy_s(name, 128, videoDesc); memory = videoMem;}

	void ResetRenderTarget();
	void UnsetRenderTarget();
	void DoingDepthCheck(bool check);

	bool ComputeSupport(){ return compute; }
private:
	bool vsync;
	int videoMem;
	char videoDesc[128];
	float clearColor[4];
	e::ComPtr<IDXGISwapChain> swapChain;
	e::ComPtr<ID3D11Device> device;
	e::ComPtr<ID3D11DeviceContext> deviceContext;
	e::ComPtr<ID3D11RenderTargetView> renderTargetView;
	e::ComPtr<ID3D11UnorderedAccessView> backBufferAccess;
	e::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	e::ComPtr<ID3D11DepthStencilState> depthStencilState;
	e::ComPtr<ID3D11DepthStencilState> depthStencilState2d;
	e::ComPtr<ID3D11DepthStencilView> depthStencilView;
	e::ComPtr<ID3D11RasterizerState> rasterState;
	e::ComPtr<ID3D11BlendState> blendState;
	D3D11_VIEWPORT viewport;
	e::XMFLOAT4X4 projectionMatrix;
	e::XMFLOAT4X4 orthoMatrix;

	static ID3D11Device *staticDevice;
	static ID3D11DeviceContext *staticContext;

	bool compute;
};

