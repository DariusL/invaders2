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
	if(!d3D.Init(width, heigth, vsync, handle, fullScreen, screenDepth, screenNear))
		return false;

	if(!App::Get()->GetResourceManager()->InitShaders(d3D.GetDevice()))
		return false;
	
	D3DXVECTOR2 viewportSize(width / 4, heigth / 4);
	floater = unique_ptr<FloatingCamera>(new FloatingCamera(viewportSize, D3DXVECTOR2(width / 2 - viewportSize.x / 2, heigth / -2 + viewportSize.y / 2)));
	floater->SetRotation(0, 0, 20);

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

bool Graphics::Init(IWorld *world)
{
	this->world = world;
	if(!world->Init(d3D.GetDevice()))
		return false;
	floater->Init(d3D.GetDevice());
	return true;
}

void Graphics::Render()
{
	D3DXMATRIX viewMatrix, projectionMatrix, transMatrix;
	shared_ptr<Light> light = world->GetLight();
	Camera &camera = world->GetCamera();
	camera.Render();

	//renderinimo informacijos struktura
	RenderParams params;
	params.brightness = brightness;//foninio apsvietimo stiprumas
	params.context = d3D.GetDeviceContext();//kontekstas
	params.lightPos = light->GetPos();//sviesos pozicija pasaulio erdveje
	params.diffuseColor = light->GetColor();//difuzines sviesos spalva

	floater->SetRenderTarget(params.context);
	floater->ClearTarget(params.context);
	
	floater->Render();
	floater->GetViewMatrix(viewMatrix);
	params.cameraPos = floater->GetPosition();
	d3D.GetProjectionMatrix(projectionMatrix);
	D3DXMatrixMultiply(&transMatrix, &viewMatrix, &projectionMatrix);

	params.transMatrix = transMatrix;

	world->Render(params);

	d3D.ResetRenderTarget();
	d3D.DoingDepthCheck(true);
	d3D.ClearRenderTarget();

	

	params.cameraPos = camera.GetPosition();

	camera.GetViewMatrix(viewMatrix);
	d3D.GetProjectionMatrix(projectionMatrix);

	D3DXMatrixMultiply(&transMatrix, &viewMatrix, &projectionMatrix);
	params.transMatrix = transMatrix;

	world->Render(params);

	d3D.DoingDepthCheck(false);

	d3D.GetOrthoMatrix(params.transMatrix);
	floater->Render(params);
	
	d3D.Present();
}