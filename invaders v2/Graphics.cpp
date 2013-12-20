#include "includes.h"
#include "Graphics.h"
#include "App.h"

Graphics::Graphics(int width, int height, HWND handle, bool fullscreen)
:handle(handle), width(width), height(height), fullScreen(fullscreen), brightness(0.1f),
post(POST_PROCESS_NONE), vsync(false), screenDepth(10000.0f), screenNear(0.1f),
d3D(width, height, vsync, handle, fullScreen, screenDepth, screenNear),
rm(d3D.GetDevice())
{
	auto device = d3D.GetDevice();

	XMFLOAT2 viewportSize(width / 4.0f, height / 4.0f);
	celTarget = make_unique<RenderTarget>(width, height);
	celTarget->Init(d3D.GetDevice());
	hBlurTarget = make_unique<Screen<TextureVertexType, HorizontalBlurShader>>(device, XMFLOAT3(0.0f, 0.0f, 0.2f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		RM::Get().GetShader<HorizontalBlurShader>(), width / 2, height / 2, (float)width, (float)height);

	vBlurTarget = make_unique<Screen<TextureVertexType, VerticalBlurShader>>(device, XMFLOAT3(0.0f, 0.0f, 0.2f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		RM::Get().GetShader<VerticalBlurShader>(), width / 2, height / 2, (float)width, (float)height);

	celOutput = make_unique<SimpleTexturedEntity>(XMFLOAT3(0.0f, 0.0f, 0.2f), ZeroVec3, rm.GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		rm.GetShader<TextureShader>(), nullptr, XMFLOAT3((float)width, (float)height, 1.0f));

	celPass = make_unique<CelPass>(rm.GetShader<CelComputeShader>(), width, height);
	tex.push_back(NULL);
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

	if (post)
	{
		if (post == POST_PROCESS_CEL)
		{
			celTarget->SetRenderTarget(context);
			celTarget->ClearTarget(context);
		}
		if (post == POST_PROCESS_BLUR)
		{
			auto &target = hBlurTarget->GetRenderTarget();
			target.SetRenderTarget(context);
			target.ClearTarget(context);
		}
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
			start = chrono::high_resolution_clock::now();
			d3D.ClearRenderTarget();
			d3D.UnsetRenderTarget();
			celPass->Pass(context, celTarget->GetRenderedTexture(), d3D.GetBackBufferUnorderedAccess());
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
		}
		if (post == POST_PROCESS_BLUR)
		{
			auto &target = vBlurTarget->GetRenderTarget();
			target.SetRenderTarget(context);
			target.ClearTarget(context);
			hBlurTarget->Render(params);
			d3D.ResetRenderTarget();
			d3D.ClearRenderTarget();
			vBlurTarget->Render(params);
		}
	}

	d3D.Present();
}