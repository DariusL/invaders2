#pragma once
#pragma warning(disable : 4005)
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <d3d11.h>
#include <DXGI.h>
#include <d3dcommon.h>
#include <d3dx10math.h>
#include <iostream>
using namespace std;

class Direct3D
{
public:
	Direct3D(void);
	~Direct3D(void){}

	bool Init(int width, int height, bool vsync, HWND whandle, bool fullscreen, float screendepth, float screennear);
	void Shutdown();

	void BeginScene();
	void EndScene();

	ID3D11Device *GetDevice(){return device;}
	ID3D11DeviceContext *GetDeviceContext(){return deviceContext;}

	void GetProjectionMatrix(D3DXMATRIX &matrix){matrix = projectionMatrix;}
	void GetOrthoMatrix(D3DXMATRIX &matrix){matrix = orthoMatrix;}

	void GetVideoCardInfo(char* name, int& memory){strcpy_s(name, 128, videoDesc); memory = videoMem;}
private:
	bool vsync;
	int videoMem;
	char videoDesc[128];
	float clearColor[4];
	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterState;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX orthoMatrix;
};

