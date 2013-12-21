#pragma once
#include "Direct3D.h"
#include "Scene.h"
#include "Screen.h"
#include "HorizontalBlurShader.h"
#include "VerticalBlurShader.h"
#include "SimplePass.h"
#include "ResourceManager.h"

class Graphics
{
	bool fullScreen;
	bool vsync;
	float screenDepth;
	float screenNear;
	float brightness;
	int width;
	int height;
	HWND handle;

	Direct3D d3D;
	ResourceManager rm;

	ComVector<ID3D11ShaderResourceView> tex;
	Screen<TextureVertexType, HorizontalBlurShader> hBlurTarget;
	Screen<TextureVertexType, VerticalBlurShader> vBlurTarget;
	RenderTarget celTarget;
	CelPass celPass;

	vector<long long> bench;
	chrono::time_point<chrono::high_resolution_clock> start, end;
	POST_PROCESS post;
public:
	Graphics(int width, int height, HWND handle, bool fullscreen);
	~Graphics(){}
	void Render(Scene &world);

	void SetBrightness(float brightness){this->brightness = brightness;}
	void ChangeBrightness(float offset);

	bool IsFullscreen(){return fullScreen;}

	ComPtr<ID3D11Device> GetDevice(){ return d3D.GetDevice(); }
};

