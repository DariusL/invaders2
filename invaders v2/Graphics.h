#pragma once
#include "Direct3D.h"
#include "SimplePass.h"
#include "BlurPass.h"
#include "BloomPass.h"
#include "ResourceManager.h"
#include "RenderTarget.h"
#include "String.h"
#include "StringPool.h"
#include "Screen.h"

class Graphics
{
	bool fullScreen;
	bool vsync;
	float screenDepth;
	float screenNear;
	float brightness;
	int width;
	int height;
	HWND hwnd;

	Direct3D d3D;
	ResourceManager rm;

	StringPool strPool;

	RenderTarget target;
	CelPass celPass;
	BlurPass blurPass;
	BloomPass bloomPass;

	vector<long long> bench;
	chrono::time_point<chrono::high_resolution_clock> start, end;
	POST_PROCESS post;
public:
	Graphics(int width, int height, HWND handle, bool fullscreen);
	~Graphics(){}
	void Render(Screen &world);

	void SetBrightness(float brightness){this->brightness = brightness;}
	void ChangeBrightness(float offset);

	bool IsFullscreen(){return fullScreen;}

	ID3D11Device *GetDevice(){ return d3D.GetDevice(); }
};

