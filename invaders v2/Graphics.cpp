#include "includes.h"
#include "Graphics.h"
#include "App.h"

Graphics::Graphics(int width, int height, HWND handle, bool fullscreen)
:handle(handle), width(width), height(height), fullScreen(fullscreen), brightness(0.1f),
post(POST_PROCESS_NONE), vsync(false), screenDepth(10000.0f), screenNear(0.1f),
d3D(width, height, vsync, handle, fullScreen, screenDepth, screenNear),
rm(d3D.GetDevice()), celPass(rm.GetShader<CelComputeShader>(), width, height),
target(d3D.GetDevice(), width, height),
blurPass(d3D.GetDevice(), width, height),
bloomPass(d3D.GetDevice(), width, height),
str(ZeroVec3, "RAND", d3D.GetDevice(), RM::Get().GetShader<ColorShader>())
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

void Graphics::Render(IWorld &world, int input)
{
	auto context = d3D.GetDeviceContext();

	d3D.DoingDepthCheck(true);

	auto &camera = world.GetCamera();

	RenderParams params;	
	params.view = camera.GetViewMatrix();
	params.projection = d3D.GetProjectionMatrix();
	params.brightness = brightness;
	params.context = context;
	params.camera = &camera;

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

	str.Render(params);
	world.Render(params);// <------------------------------------------CIA RENDERINA

	if (post)
	{
		d3D.ClearRenderTarget();
		d3D.UnsetRenderTarget();
		if (post == POST_PROCESS_CEL)
		{
			celPass.Pass(context, target.GetRenderedTexture(), d3D.GetBackBufferUnorderedAccess());
		}
		else if (post == POST_PROCESS_BLUR)
		{
			blurPass.Pass(context, target.GetRenderedTexture(), d3D.GetBackBufferUnorderedAccess());
		}
		else if (post == POST_PROCESS_BLOOM)
		{
			bloomPass.Pass(context, target.GetRenderedTexture(), d3D.GetBackBufferUnorderedAccess());
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