#pragma once
#include <Windows.h>

#include "Direct3D.h"
#include "Camera.h"
#include "World.h"
#include "Globals.h"
#include "App.h"
#include "GraphicsObject.h"
#include "TheEntireActualGraphics.h"

class App;
class Graphics
{
	Direct3D *d3D;
	Camera *camera;

	GraphicsObject *mainObject;

	bool fullScreen;
	bool vsync;
	float screenDepth;
	float screenNear;
public:
	Graphics(void);
	~Graphics(void){}

	bool Init(int width, int height, HWND handle, bool fullscreen, World* world);
	void Shutdown();
	void Render();

	bool IsFullscreen(){return fullScreen;}
};

