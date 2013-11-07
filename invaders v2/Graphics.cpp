#include "includes.h"
#include "Graphics.h"
#include "App.h"

Graphics::Graphics(void)
{
	screenDepth = 1000.0f;
	screenNear = 0.1f;
	vsync = false;
}

Graphics::~Graphics()
{
}

void Graphics::Init(int width, int heigth, HWND handle, bool fullscreen, float brightness)
{
	this->handle = handle;
	this->fullScreen = fullscreen;
	this->brightness = brightness;
	this->width = width;
	this->height = heigth;
	d3D.Init(width, heigth, vsync, handle, fullScreen, screenDepth, screenNear);

	App::Get()->GetResourceManager()->InitShaders(d3D.GetDevice());
	
	D3DXVECTOR2 viewportSize(width / 4.0f, heigth / 4.0f);
}

void Graphics::ChangeBrightness(float offset)
{
	brightness += offset;
	if(brightness > 1.0f)
		brightness = 1.0f;
	else if(brightness < 0.0f)
		brightness = 0.0f;
}

void Graphics::Init(Scene *world)
{
	this->world = world;
	world->Init(d3D.GetDevice());
}

void Graphics::Render()
{
	D3DXMATRIX projectionMatrix;

	auto &light = world->GetLight();
	auto &camera = world->GetCamera();
	auto &remote = world->GetRemoteCamera();
	auto &target = remote.GetRenderTarget();

	d3D.GetProjectionMatrix(projectionMatrix);

	camera.RenderMain();
	remote.RenderMain();

	RenderParams params;
	params.brightness = brightness;
	params.context = d3D.GetDeviceContext();
	params.lightPos = light.GetPos();
	params.diffuseColor = light.GetColor();
	params.cameraPos = remote.GetPosition(); 

	D3DXMatrixMultiply(&params.transMatrix, &remote.GetViewMatrix(), &projectionMatrix);

	target.SetRenderTarget(params.context);
	target.ClearTarget(params.context);

	world->Render(params);

	d3D.ResetRenderTarget();
	d3D.ClearRenderTarget();
	params.cameraPos = camera.GetPosition();
	D3DXMatrixMultiply(&params.transMatrix, &camera.GetViewMatrix(), &projectionMatrix);

	world->Render(params);
	remote.Render(params);

	d3D.Present();
}