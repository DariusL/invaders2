#include "includes.h"
#include "Graphics.h"
#include "App.h"

Graphics::Graphics(void)
{
	screenDepth = 1000.0f;
	screenNear = 0.1f;
	vsync = false;
}

void Graphics::Init(int width, int heigth, HWND handle, bool fullscreen, float brightness)
{
	this->handle = handle;
	this->fullScreen = fullscreen;
	this->brightness = brightness;
	this->width = width;
	this->height = heigth;
	d3D.Init(width, heigth, vsync, handle, fullScreen, screenDepth, screenNear);

	RM::Get().InitShaders(d3D.GetDevice());
	
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

void Graphics::Init(Scene &world)
{
	world.Init(d3D.GetDevice());
}

void Graphics::Render(Scene &world)
{
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX reflectionMatrix;
	D3DXMATRIX zeroReflect;
	D3DXVECTOR4 plane;
	auto context = d3D.GetDeviceContext();

	auto &light = world.GetLight();
	auto &camera = world.GetCamera();
	auto &remotes = world.GetRemoteCameras();
	auto &mirrors = world.GetMirrors();
	d3D.GetProjectionMatrix(projectionMatrix);

	RenderParams params;
	params.brightness = brightness;
	params.context = context;
	params.lightPos = light.GetPos();
	params.diffuseColor = light.GetColor();
	params.projection = projectionMatrix;

	for (auto &remote : remotes)
	{
		params.cameraPos = remote.GetPosition();
		for (auto &mirror : mirrors)
		{
			D3DXMatrixReflect(&reflectionMatrix, &mirror.GetMirrorPlane());
			D3DXMatrixReflect(&zeroReflect, &mirror.GetZeroPlane());
			params.view = remote.GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
			auto &target = mirror.GetRenderTarget();
			target.SetRenderTarget(context);
			target.ClearTarget(context);
			params.clipPlane = mirror.GetMirrorPlane();
			world.Render(params);
		}
		auto &target = remote.GetRenderTarget();
		target.SetRenderTarget(context);
		target.ClearTarget(context);
		params.view = remote.GetViewMatrix();
		for (auto &mirror : mirrors)
		{
			D3DXMatrixReflect(&reflectionMatrix, &mirror.GetMirrorPlane());
			D3DXMatrixReflect(&zeroReflect, &mirror.GetZeroPlane());
			params.reflecMatrix = remote.GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
			mirror.Render(params);
		}
		params.clipPlane = ZeroPlane;
		world.Render(params);
	}

	params.cameraPos = camera.GetPosition();
	for (auto &mirror : mirrors)
	{
		D3DXMatrixReflect(&reflectionMatrix, &mirror.GetMirrorPlane());
		D3DXMatrixReflect(&zeroReflect, &mirror.GetZeroPlane());
		params.view = camera.GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
		auto &target = mirror.GetRenderTarget();
		target.SetRenderTarget(context);
		target.ClearTarget(context);
		params.clipPlane = mirror.GetMirrorPlane();
		world.Render(params);
	}

	d3D.ResetRenderTarget();
	d3D.ClearRenderTarget();
	D3DXMatrixReflect(&reflectionMatrix, &mirrors[0].GetMirrorPlane());
	params.view = camera.GetViewMatrix();

	params.clipPlane = ZeroPlane;
	world.Render(params);
	for (auto &remote : remotes)
	{
		remote.Render(params);
	}
	for (auto &mirror : mirrors)
	{
		D3DXMatrixReflect(&reflectionMatrix, &mirror.GetMirrorPlane());
		D3DXMatrixReflect(&zeroReflect, &mirror.GetZeroPlane());
		params.reflecMatrix = camera.GetReflectedViewMatrix(reflectionMatrix ,zeroReflect);
		mirror.Render(params);
	}

	d3D.Present();
}