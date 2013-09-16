#pragma once
#include "Direct3D.h"
#include "Camera.h"
#include "IWorld.h"

class Graphics
{
	Direct3D d3D;

	IWorld *world;

	bool fullScreen;
	bool vsync;
	float screenDepth;
	float screenNear;
	float brightness;
	HWND handle;
public:
	Graphics(void);
	~Graphics(void);

	bool Init(int width, int height, HWND handle, bool fullscreen, float brightness);
	bool Init(IWorld *world);
	void Render();

	void SetBrightness(float brightness){this->brightness = brightness;}
	void ChangeBrightness(float offset);

	bool IsFullscreen(){return fullScreen;}
};

