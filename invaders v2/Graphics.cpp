#include "includes.h"
#include "Graphics.h"
#include "App.h"
#include "Button.h"
#include "Settings.h"

Graphics::Graphics(int width, int height, HWND handle, bool fullscreen)
	:hwnd(handle), width(width), height(height), fullScreen(fullscreen), brightness(0.1f),
	vsync(false), screenDepth(10000.0f), screenNear(0.1f),
	d3D(width, height, vsync, handle, fullScreen, screenDepth, screenNear),
	rm(d3D.GetDevice(), d3D.ComputeSupport()),
	target(d3D.GetDevice(), width, height),
	strPool(d3D.GetDevice())
{
	auto device = d3D.GetDevice();

	XMFLOAT2 viewportSize(width / 4.0f, height / 4.0f);
	copyPass = make_unique<CopyPass>(RM::Get().GetShader<CopyComputeShader>(), width, height);
	blurPass = make_unique<BlurPass>(d3D.GetDevice(), width, height);
	bloomPass = make_unique<BloomPass>(d3D.GetDevice(), width, height);
	or = SettingsObservers::Register(Settings::KEY_POST, e::bind(&Graphics::SetPost, this, e::placeholders::_1));
	post = Settings::Get().GetValue(Settings::KEY_POST) != 0;
}

void Graphics::ChangeBrightness(float offset)
{
	brightness += offset;
	if(brightness > 1.0f)
		brightness = 1.0f;
	else if(brightness < 0.0f)
		brightness = 0.0f;
}

void Graphics::SetPost(int post)
{
	this->post = post != 0;
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

	if (post)
	{
		params.pass = PASS_BACK;
		target.SetRenderTarget(context);
		target.ClearTarget(context);
		world.Render(params);

		d3D.UnsetRenderTarget();
		blurPass->Pass(context, target.GetRenderedTexture(), target.GetUnorderedAccess());
		target.SetRenderTarget(context);
		params.pass = PASS_FRONT;
		world.Render(params);
		d3D.UnsetRenderTarget();
		bloomPass->Pass(context, target.GetRenderedTexture(), d3D.GetBackBufferUnorderedAccess());
	}
	else
	{
		d3D.ResetRenderTarget();
		d3D.ClearRenderTarget();
		params.pass = PASS_FRONT;
		world.Render(params);
	}

	d3D.Present();
}