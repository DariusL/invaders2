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
	D3DXMATRIX reflectionMatrix;
	auto context = d3D.GetDeviceContext();

	auto &light = world->GetLight();
	auto &camera = world->GetCamera();
	auto &remotes = world->GetRemoteCamera();
	d3D.GetProjectionMatrix(projectionMatrix);

	camera.RenderMain();

	RenderParams params;
	params.brightness = brightness;
	params.context = context;
	params.lightPos = light.GetPos();
	params.diffuseColor = light.GetColor();

	for (auto &remote : remotes)
	{
		remote.RenderMain();
		params.cameraPos = remote.GetPosition();
		params.transMatrix = remote.GetViewMatrix() * projectionMatrix;
		auto &target = remote.GetRenderTarget();
		target.SetRenderTarget(context);
		target.ClearTarget(context);
		world->Render(params);
	}

	d3D.ResetRenderTarget();
	d3D.ClearRenderTarget();

	params.transMatrix = camera.GetViewMatrix() * projectionMatrix;

	world->Render(params);
	for (auto &remote : remotes)
	{
		remote.Render(params);
	}

	d3D.Present();
}