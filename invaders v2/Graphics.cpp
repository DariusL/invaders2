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
	
	XMFLOAT2 viewportSize(width / 4.0f, heigth / 4.0f);
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
	XMMATRIX reflectionMatrix;
	XMMATRIX zeroReflect;
	XMFLOAT4 plane;
	auto context = d3D.GetDeviceContext();

	auto &light = world.GetLight();
	auto &camera = world.GetCamera();
	auto &remotes = world.GetRemoteCameras();
	auto &mirrors = world.GetMirrors();
	auto &water = world.GetWater();

	RenderParams params;
	params.brightness = brightness;
	params.context = context;
	params.lightPos = light.GetPos();
	params.diffuseColor = light.GetColor();
	params.projection = d3D.GetProjectionMatrix();
	params.waterScale = 0.1f;
	long time = clock();
	time %= 5000;
	params.waterTranslation = XMFLOAT2(time / 5000.0f, 0.0f);

	for (auto &remote : remotes)
	{
		params.cameraPos = remote.GetPosition();
		for (auto &mirror : mirrors)
		{
			reflectionMatrix = DirectX::XMMatrixReflect(mirror.GetMirrorPlane());
			zeroReflect = DirectX::XMMatrixReflect(mirror.GetZeroPlane());
			params.view = remote.GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
			auto &target = mirror.GetRenderTarget();
			target.SetRenderTarget(context);
			target.ClearTarget(context);
			XMStoreFloat4(&params.clipPlane, mirror.GetMirrorPlane());
			world.Render(params);
		}
		{
			auto &reflect = water.GetRenderTarget();
			auto &refract = water.GetRefractionTarget();
			reflectionMatrix = DirectX::XMMatrixReflect(water.GetMirrorPlane());
			zeroReflect = DirectX::XMMatrixReflect(water.GetZeroPlane());
			params.view = remote.GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
			reflect.SetRenderTarget(context);
			reflect.ClearTarget(context);
			XMStoreFloat4(&params.clipPlane, water.GetMirrorPlane());
			world.Render(params);

			params.view = remote.GetViewMatrix();
			refract.SetRenderTarget(context);
			refract.ClearTarget(context);
			XMStoreFloat4(&params.clipPlane, water.GetReversePlane());
			world.Render(params);
		}
		auto &target = remote.GetRenderTarget();
		target.SetRenderTarget(context);
		target.ClearTarget(context);
		params.view = remote.GetViewMatrix();
		params.clipPlane = ZeroVec4;
		for (auto &mirror : mirrors)
		{
			reflectionMatrix = DirectX::XMMatrixReflect(mirror.GetMirrorPlane());
			zeroReflect = DirectX::XMMatrixReflect(mirror.GetZeroPlane());
			params.reflecMatrix = remote.GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
			mirror.Render(params);
		}
		params.reflecMatrix = remote.GetReflectedViewMatrix(DirectX::XMMatrixReflect(water.GetMirrorPlane()), DirectX::XMMatrixReflect(water.GetZeroPlane()));
		water.Render(params);
		world.Render(params);
	}

	params.cameraPos = camera.GetPosition();
	for (auto &mirror : mirrors)
	{
		reflectionMatrix = DirectX::XMMatrixReflect(mirror.GetMirrorPlane());
		zeroReflect = DirectX::XMMatrixReflect(mirror.GetZeroPlane());
		params.view = camera.GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
		auto &target = mirror.GetRenderTarget();
		target.SetRenderTarget(context);
		target.ClearTarget(context);
		XMStoreFloat4(&params.clipPlane, mirror.GetMirrorPlane());
		world.Render(params);
	}

	{
		auto &reflect = water.GetRenderTarget();
		auto &refract = water.GetRefractionTarget();
		reflectionMatrix = DirectX::XMMatrixReflect(water.GetMirrorPlane());
		zeroReflect = DirectX::XMMatrixReflect(water.GetZeroPlane());
		params.view = camera.GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
		reflect.SetRenderTarget(context);
		reflect.ClearTarget(context);
		XMStoreFloat4(&params.clipPlane, water.GetMirrorPlane());
		world.Render(params);

		params.view = camera.GetViewMatrix();
		refract.SetRenderTarget(context);
		refract.ClearTarget(context);
		XMStoreFloat4(&params.clipPlane, water.GetReversePlane());
		world.Render(params);
	}

	d3D.ResetRenderTarget();
	d3D.ClearRenderTarget();
	params.view = camera.GetViewMatrix();

	params.clipPlane = ZeroVec4;
	params.reflecMatrix = camera.GetReflectedViewMatrix(DirectX::XMMatrixReflect(water.GetMirrorPlane()), DirectX::XMMatrixReflect(water.GetZeroPlane()));
	water.Render(params);
	world.Render(params);
	for (auto &remote : remotes)
	{
		remote.Render(params);
	}
	for (auto &mirror : mirrors)
	{
		reflectionMatrix = DirectX::XMMatrixReflect(mirror.GetMirrorPlane());
		zeroReflect = DirectX::XMMatrixReflect(mirror.GetZeroPlane());
		params.reflecMatrix = camera.GetReflectedViewMatrix(reflectionMatrix ,zeroReflect);
		mirror.Render(params);
	}

	d3D.Present();
}