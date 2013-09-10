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
	return true;
}

void Graphics::Render()
{
	D3DXMATRIX viewMatrix, projectionMatrix, transMatrix;

	// Clear the buffers to begin the scene.
	d3D.BeginScene();

	// Generate the view matrix based on the camera's position.
	Camera &camera = world->GetCamera();
	camera.Render();

	camera.GetViewMatrix(viewMatrix);
	d3D.GetProjectionMatrix(projectionMatrix);
	D3DXMatrixMultiply(&transMatrix, &viewMatrix, &projectionMatrix);

	RenderParams params;
	params.brightness = brightness;
	params.context = d3D.GetDeviceContext();
	params.transMatrix = transMatrix;

	world->Render(params);

	d3D.EndScene();
}