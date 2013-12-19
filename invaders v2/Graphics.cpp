#include "includes.h"
#include "Graphics.h"
#include "App.h"

Graphics::Graphics(void)
{
	screenDepth = 10000.0f;
	screenNear = 0.1f;
	vsync = false;
	post = POST_PROCESS_CEL;
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

	auto &rm = RM::Get();
	auto device = d3D.GetDevice();
	
	XMFLOAT2 viewportSize(width / 4.0f, heigth / 4.0f);
	celTarget = make_unique<RenderTarget>(width, height);
	celTarget->Init(d3D.GetDevice());
	hBlurTarget = make_unique<Screen<TextureVertexType, HorizontalBlurShader>>(XMFLOAT3(0.0f, 0.0f, 0.2f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		RM::Get().GetShader<HorizontalBlurShader>(), width / 2, height / 2, (float)width, (float)height);
	hBlurTarget->Init(d3D.GetDevice());
	vBlurTarget = make_unique<Screen<TextureVertexType, VerticalBlurShader>>(XMFLOAT3(0.0f, 0.0f, 0.2f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		RM::Get().GetShader<VerticalBlurShader>(), width / 2, height / 2, (float)width, (float)height);
	vBlurTarget->Init(d3D.GetDevice());
	celOutput = make_unique<SimpleTexturedEntity>(XMFLOAT3(0.0f, 0.0f, 0.2f), ZeroVec3, rm.GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		rm.GetShader<TextureShader>(), nullptr, XMFLOAT3((float)width, (float)height, 1.0f));
	celOutput->Init(device);
	celPass = make_unique<CelPass>(rm.GetShader<CelComputeShader>(), width, height);
	celPass->Init(device);
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

void Graphics::Init(Scene &world)
{
	world.Init(d3D.GetDevice());
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
			d3D.ResetRenderTarget();
			d3D.ClearRenderTarget();
			auto t = celPass->Pass(context, celTarget->GetRenderedTexture());
			tex[0] = t;
			celOutput->Render(params, tex);
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