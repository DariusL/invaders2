#pragma once
#include "Direct3D.h"
#include "Scene.h"

class Graphics
{
	Direct3D d3D;

	bool fullScreen;
	bool vsync;
	float screenDepth;
	float screenNear;
	float brightness;
	int width;
	int height;
	HWND handle;

	unique_ptr<SimpleTexturedEntity> hud;
	ComVector<ID3D11ShaderResourceView> tex;
public:
	Graphics();
	~Graphics(void){}
	void Init(Scene &world);
	void Init(int width, int height, HWND handle, bool fullscreen, float brightness);
	void Render(Scene &world);

	void SetBrightness(float brightness){this->brightness = brightness;}
	void ChangeBrightness(float offset);

	bool IsFullscreen(){return fullScreen;}
};

