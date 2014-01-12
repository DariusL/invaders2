#pragma once
#include "Direct3D.h"
#include "Scene.h"
#include "Screen.h"
#include "SimplePass.h"
#include "BlurPass.h"
#include "BloomPass.h"
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

	RenderTarget target;
	CelPass celPass;
	BlurPass blurPass;
	BloomPass bloomPass;

	vector<long long> bench;
	chrono::time_point<chrono::high_resolution_clock> start, end;
	POST_PROCESS post;

	vector<RemoteCamera*> cameras;
	vector<MirrorBall*> reflectives;
public:
	Graphics(int width, int height, HWND handle, bool fullscreen);
	~Graphics(){}
	void Render(Scene &world, int input);
	void LoadThings(Scene &world);

	void SetBrightness(float brightness){this->brightness = brightness;}
	void ChangeBrightness(float offset);

	bool IsFullscreen(){return fullScreen;}

	ComPtr<ID3D11Device> GetDevice(){ return d3D.GetDevice(); }
};

