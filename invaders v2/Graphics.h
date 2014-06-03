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
#include "Observers.h"

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

	bool post;
	e::unique_ptr<CopyPass> copyPass;
	e::unique_ptr<BlurPass> blurPass;
	e::unique_ptr<BloomPass> bloomPass;

	SettingsObservers::ObserverScopeRef or;
public:
	Graphics(int width, int height, HWND handle, bool fullscreen);
	~Graphics(){}
	void Render(Screen &world);

	void SetBrightness(float brightness){this->brightness = brightness;}
	void ChangeBrightness(float offset);

	bool IsFullscreen(){return fullScreen;}

	ID3D11Device *GetDevice(){ return d3D.GetDevice(); }
	void SetPost(int post);
};

