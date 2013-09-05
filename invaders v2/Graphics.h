#pragma once
#include <Windows.h>

#include "Direct3D.h"
#include "Camera.h"
#include "World.h"
#include "Globals.h"

class Graphics
{
	Direct3D d3D;
	Camera camera;

	World *world;

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
	bool Init(World *world);
	void Render();

	void SetBrightness(float brightness){this->brightness = brightness;}
	void ChangeBrightness(float offset);

	bool IsFullscreen(){return fullScreen;}
};

