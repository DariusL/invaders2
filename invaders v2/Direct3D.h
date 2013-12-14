#pragma once

#include "includes.h"
#include "Utils.h"

using namespace std;
using namespace Microsoft::WRL;

class Direct3D
{
public:
	Direct3D(void);
	~Direct3D(void);

	void Init(int width, int height, bool vsync, HWND whandle, bool fullscreen, float screendepth, float screennear);

	void ClearRenderTarget();
	void Present();

	ComPtr<ID3D11Device> GetDevice(){return device;}
	ComPtr<ID3D11DeviceContext> GetDeviceContext(){return deviceContext;}

	XMMATRIX GetProjectionMatrix(){ return XMLoadFloat4x4(&projectionMatrix); }
	XMMATRIX GetOrthoMatrix(){ return XMLoadFloat4x4(&orthoMatrix); }

	void GetVideoCardInfo(char* name, int& memory){strcpy_s(name, 128, videoDesc); memory = videoMem;}

	void ResetRenderTarget();
	void DoingDepthCheck(bool check);
private:
	bool vsync;
	int videoMem;
	char videoDesc[128];
	float clearColor[4];
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	ComPtr<ID3D11DepthStencilState> depthStencilState;
	ComPtr<ID3D11DepthStencilState> depthStencilState2d;
	ComPtr<ID3D11DepthStencilView> depthStencilView;
	ComPtr<ID3D11RasterizerState> rasterState;
	ComPtr<ID3D11BlendState> blendState;
	D3D11_VIEWPORT viewport;
	XMFLOAT4X4 projectionMatrix;
	XMFLOAT4X4 orthoMatrix;
};

