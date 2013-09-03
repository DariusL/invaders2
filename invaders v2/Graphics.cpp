#include "Graphics.h"

Graphics::Graphics(void)
{
	d3D = NULL;
	screenDepth = 1000.0f;
	screenNear = 0.1f;
	vsync = false;
	camera = NULL;
}

Graphics::~Graphics()
{
	if(d3D)
	{
		delete d3D;
		d3D = NULL;
	}

	if(camera)
	{
		delete camera;
		camera = NULL;
	}
}

bool Graphics::Init(int width, int heigth, HWND handle, bool fullscreen, float brightness)
{
	d3D = new Direct3D();
	this->handle = handle;
	this->fullScreen = fullscreen;
	this->brightness = brightness;
	if(!d3D->Init(width, heigth, vsync, handle, fullScreen, screenDepth, screenNear))
	{
		MessageBox(handle, L"Could not intialize DirectX", L"Error", MB_OK);
		return false;
	}
	// Create the camera object.
	camera = new Camera;

	// Set the initial position of the camera.
	camera->SetPosition(0.0f, 0.0f, -50.0f);

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

bool Graphics::Init(World *world)
{
	this->world = world;
	if(!world->Init(d3D->GetDevice(), handle))
		return false;
	return true;
}

void Graphics::Render()
{
	D3DXMATRIX viewMatrix, projectionMatrix, transMatrix;

	// Clear the buffers to begin the scene.
	d3D->BeginScene();

	// Generate the view matrix based on the camera's position.
	camera->Render();

	camera->GetViewMatrix(viewMatrix);
	d3D->GetProjectionMatrix(projectionMatrix);
	D3DXMatrixMultiply(&transMatrix, &viewMatrix, &projectionMatrix);

	RenderParams params;
	params.brightness = brightness;
	params.context = d3D->GetDeviceContext();
	params.transMatrix = transMatrix;

	world->Render(params);

	d3D->EndScene();
}