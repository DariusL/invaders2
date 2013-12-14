#include "includes.h"
#include "Graphics.h"
#include "App.h"

Graphics::Graphics(void)
{
	screenDepth = 10000.0f;
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
	hudDepth = make_unique<SimpleTexturedEntity>(XMFLOAT3(300.0f, 150.0f, 1.0f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE), 
		RM::Get().GetShader<TextureShader>(), nullptr, XMFLOAT3(200.0f, 200.0f, 1.0f));
	hudDepth->Init(d3D.GetDevice());
	hudBack = make_unique<SimpleTexturedEntity>(XMFLOAT3(300.0f, -150.0f, 1.0f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		RM::Get().GetShader<TextureShader>(), nullptr, XMFLOAT3(200.0f, 200.0f, 1.0f));
	hudBack->Init(d3D.GetDevice());
	harbinger = make_unique<SimpleTexturedEntity>(XMFLOAT3(0.0f, 0.0f, 0.2f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		RM::Get().GetShader<TextureShader>(), RM::Get().GetTexture(RM::TEXTURE_GABEN), XMFLOAT3((float)width, (float)heigth, 1.0f));
	harbinger->Init(d3D.GetDevice());
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

	d3D.ResetRenderTarget();
	d3D.ClearRenderTarget();
	params.view = camera.GetViewMatrix();
	params.projection = d3D.GetProjectionMatrix();
	params.camera = &camera;
	params.clipPlane = ZeroVec4;
	params.pass = PASS_TYPE_NORMAL;
	world.Render(params); 

	d3D.DoingDepthCheck(false);
	params.projection = d3D.GetOrthoMatrix();
	params.view = XMMatrixIdentity();
	tex[0] = light.GetRenderedTexture();
	hudDepth->Render(params, tex);
	tex[0] = light.GetOtherTexture();
	hudBack->Render(params, tex);
	//harbinger->Render(params);

	d3D.Present();
}