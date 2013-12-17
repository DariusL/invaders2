#pragma once
#include "Direct3D.h"
#include "Scene.h"
#include "Screen.h"
#include "CelShader.h"
#include "HorizontalBlurShader.h"
#include "VerticalBlurShader.h"

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

	ComVector<ID3D11ShaderResourceView> tex;
	unique_ptr<Screen<TextureVertexType, HorizontalBlurShader>> hBlurTarget;
	unique_ptr<Screen<TextureVertexType, VerticalBlurShader>> vBlurTarget;
	unique_ptr<Screen<TextureVertexType, CelShader>> celTarget;
	POST_PROCESS post;
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

