#pragma once
#include "Direct3D.h"
#include "Scene.h"

class Graphics
{
	Direct3D d3D;

	Scene *world;

	bool fullScreen;
	bool vsync;
	float screenDepth;
	float screenNear;
	float brightness;
	int width;
	int height;
	HWND handle;
public:
	Graphics(void);
	~Graphics(void);

	void Init(int width, int height, HWND handle, bool fullscreen, float brightness);
	void Init(Scene *world);
	void Render();

	void SetBrightness(float brightness){this->brightness = brightness;}
	void ChangeBrightness(float offset);

	bool IsFullscreen(){return fullScreen;}
};

