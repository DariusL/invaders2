#include "includes.h"
#include "Graphics.h"
#include "App.h"

Graphics::Graphics(int width, int height, HWND handle, bool fullscreen)
:handle(handle), width(width), height(height), fullScreen(fullscreen), brightness(0.1f),
post(POST_PROCESS_BLUR), vsync(false), screenDepth(10000.0f), screenNear(0.1f),
d3D(width, height, vsync, handle, fullScreen, screenDepth, screenNear),
rm(d3D.GetDevice()), celPass(rm.GetShader<CelComputeShader>(), width, height),
target(d3D.GetDevice(), width, height),
blurPass(d3D.GetDevice(), width, height)
{
	auto device = d3D.GetDevice();

	XMFLOAT2 viewportSize(width / 4.0f, height / 4.0f);
}

void Graphics::ChangeBrightness(float offset)
{
	brightness += offset;
	if(brightness > 1.0f)
		brightness = 1.0f;
	else if(brightness < 0.0f)
		brightness = 0.0f;
}

void Graphics::Render(Scene &world)
{
	auto context = d3D.GetDeviceContext();

	d3D.DoingDepthCheck(true);

	auto &light = world.GetLight();
	auto &camera = world.GetCamera();

	vector<MirrorBall*> reflectives;
	vector<RemoteCamera*> cameras;
	world.GetRenderBalls(reflectives, cameras);

	RenderParams params;
	params.brightness = brightness;
	params.context = context;
	params.diffuseColor = light.GetColor();
	params.waterScale = 0.1f;
	long time = clock();
	time %= 5000;
	params.waterTranslation = XMFLOAT2(time / 5000.0f, 0.0f);

	params.camera = &camera;
	light.Prepare(params);
	world.Render(params);

	params.shadowMap = light.GetRenderedTexture();

	for (auto remote : cameras)
	{
		params.camera = remote;
		for (auto target : reflectives)
		{
			target->Prepare(context, params);
			world.Render(params);
			target->Swap();
		}
		auto &ball = remote->GetCameraBall();
		ball.Prepare(context, params, d3D);
		world.Render(params);
		ball.Swap();
	}

	params.camera = &camera;

	for (auto &target : reflectives)
	{
		target->Prepare(context, params);
		world.Render(params);
		target->Swap();
	}
	start = chrono::high_resolution_clock::now();
	if (post)
	{
		target.SetRenderTarget(context);
		target.ClearTarget(context);
	}
	else
	{
		d3D.ResetRenderTarget();
		d3D.ClearRenderTarget();
	}
	params.view = camera.GetViewMatrix();
	params.projection = d3D.GetProjectionMatrix();
	params.camera = &camera;
	params.clipPlane = ZeroVec4;
	params.pass = PASS_TYPE_NORMAL;
	world.Render(params); 

	d3D.DoingDepthCheck(false);
	params.projection = d3D.GetOrthoMatrix();
	params.view = XMMatrixIdentity();

	if (post)
	{
		if (post == POST_PROCESS_CEL)
		{
			d3D.ClearRenderTarget();
			d3D.UnsetRenderTarget();
			celPass.Pass(context, target.GetRenderedTexture(), d3D.GetBackBufferUnorderedAccess());
		}
		if (post == POST_PROCESS_BLUR)
		{
			d3D.ClearRenderTarget();
			d3D.UnsetRenderTarget();
			blurPass.Pass(context, target.GetRenderedTexture(), d3D.GetBackBufferUnorderedAccess());
		}
	}

	end = chrono::high_resolution_clock::now();
	bench.push_back(chrono::duration_cast<chrono::microseconds>(end - start).count());
	if (bench.size() >= 20)
	{
		double time = 0;
		for (auto &t : bench)
			time += t;
		time /= 20.0f;
		wstring s = to_wstring(time) + L"\r\n";
		OutputDebugString(s.c_str());
		bench.clear();
	}
	d3D.Present();
}