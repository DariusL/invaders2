#pragma once
#pragma warning(disable : 4005)
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include "includes.h"

#include "Utils.h"

using namespace std;
using namespace Microsoft::WRL;

class Direct3D
{
public:
	Direct3D(void);
	~Direct3D(void);

	bool Init(int width, int height, bool vsync, HWND whandle, bool fullscreen, float screendepth, float screennear);

	void ClearRenderTarget();
	void Present();

	ComPtr<ID3D11Device> GetDevice(){return device;}
	ComPtr<ID3D11DeviceContext> GetDeviceContext(){return deviceContext;}

	void GetProjectionMatrix(D3DXMATRIX &matrix){matrix = projectionMatrix;}
	void GetOrthoMatrix(D3DXMATRIX &matrix){matrix = orthoMatrix;}

	void GetVideoCardInfo(char* name, int& memory){strcpy_s(name, 128, videoDesc); memory = videoMem;}

	void SetRenderTarget(ComPtr<ID3D11RenderTargetView> target);
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
	ComPtr<ID3D11RenderTargetView> mainRenderTargetView;
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	ComPtr<ID3D11DepthStencilState> depthStencilState;
	ComPtr<ID3D11DepthStencilState> depthStencilState2d;
	ComPtr<ID3D11DepthStencilView> depthStencilView;
	ComPtr<ID3D11RasterizerState> rasterState;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX orthoMatrix;
};

