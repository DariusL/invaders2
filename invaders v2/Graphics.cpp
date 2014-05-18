#include "includes.h"
#include "Graphics.h"
#include "App.h"
#include "Button.h"

Graphics::Graphics(int width, int height, HWND handle, bool fullscreen)
	:hwnd(handle), width(width), height(height), fullScreen(fullscreen), brightness(0.1f),
	vsync(false), screenDepth(10000.0f), screenNear(0.1f),
	d3D(width, height, vsync, handle, fullScreen, screenDepth, screenNear),
	rm(d3D.GetDevice()),
	target(d3D.GetDevice(), width, height),
	strPool(d3D.GetDevice()),
	dof(true),
	copyPass(RM::Get().GetShader<CopyComputeShader>(), width, height),
	blurPass(d3D.GetDevice(), width, height),
	bloomPass(d3D.GetDevice(), width, height)
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

void Graphics::Render(Screen &world)
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
	params.gray = false;

	if (dof)
	{
		params.pass = PASS_BACK;
		target.SetRenderTarget(context);
		target.ClearTarget(context);
		world.Render(params);

		d3D.UnsetRenderTarget();
		blurPass.Pass(context, target.GetRenderedTexture(), target.GetUnorderedAccess());
		target.SetRenderTarget(context);
		params.pass = PASS_FRONT;
		world.Render(params);
		d3D.UnsetRenderTarget();
		bloomPass.Pass(context, target.GetRenderedTexture(), d3D.GetBackBufferUnorderedAccess());
	}
	else
	{
		d3D.ResetRenderTarget();
		d3D.ClearRenderTarget();
		params.pass = PASS_ALL;
		world.Render(params);
	}

	d3D.Present();
}