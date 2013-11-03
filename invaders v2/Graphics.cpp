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

bool Graphics::Init(int width, int heigth, HWND handle, bool fullscreen, float brightness)
{
	this->handle = handle;
	this->fullScreen = fullscreen;
	this->brightness = brightness;
	this->width = width;
	this->height = heigth;
	if(!d3D.Init(width, heigth, vsync, handle, fullScreen, screenDepth, screenNear))
		return false;

	if(!App::Get()->GetResourceManager()->InitShaders(d3D.GetDevice()))
		return false;
	
	D3DXVECTOR2 viewportSize(width / 4.0f, heigth / 4.0f);

	return true;
}

void Graphics::ChangeBrightness(float offset)
{
	brightness += offset;
	if(brightness > 1.0f)
		brightness = 1.0f;
	else if(brightness < 0.0f)
		brightness = 0.0f;
}

bool Graphics::Init(Scene *world)
{
	this->world = world;
	if(!world->Init(d3D.GetDevice()))
		return false;
	return true;
}

void Graphics::Render()
{
	D3DXMATRIX viewMatrix, projectionMatrix;
	auto light = world->GetLight();

	Camera &camera = world->GetCamera();
	camera.Render();
	camera.RenderMirror();

	RenderParams params;
	params.brightness = brightness;
	params.context = d3D.GetDeviceContext();
	params.lightPos = light->GetPos();
	params.diffuseColor = light->GetColor();
	params.cameraPos = camera.GetPosition();

	d3D.GetProjectionMatrix(projectionMatrix);

	auto water = world->GetWater();
	auto target = water->GetRenderTarget();
	target->SetRenderTarget(params.context);
	target->ClearTarget(params.context);
	camera.GetMirrorMatrix(viewMatrix);
	D3DXMatrixMultiply(&params.transMatrix, &viewMatrix, &projectionMatrix);
	world->Render(params);

	d3D.ResetRenderTarget();
	d3D.ClearRenderTarget();
	d3D.DoingDepthCheck(true);

	camera.GetViewMatrix(viewMatrix);
	D3DXMatrixMultiply(&params.transMatrix, &viewMatrix, &projectionMatrix);

	world->Render(params);
	water->Render(params);

	d3D.Present();
}