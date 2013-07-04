#include "Graphics.h"

Graphics::Graphics(void)
{
	d3D = NULL;
	screenDepth = 1000.0f;
	screenNear = 0.1f;
	vsync = false;
	camera = NULL;
}

bool Graphics::Init(int width, int heigth, HWND handle, bool fullscreen, World* world)
{
	d3D = new Direct3D();
	fullScreen = fullscreen;
	if(!d3D->Init(width, heigth, vsync, handle, fullScreen, screenDepth, screenNear))
	{
		MessageBox(handle, L"Could not intialize DirectX", L"Error", MB_OK);
		return false;
	}
	// Create the camera object.
	camera = new Camera;

	// Set the initial position of the camera.
	camera->SetPosition(0.0f, 0.0f, -30.0f);

	mainObject = new TheEntireActualGraphics();

	if(!mainObject->Init(d3D->GetDevice(), world, handle))
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

	mainObject->Render(d3D->GetDeviceContext(), transMatrix);

	d3D->EndScene();
}

void Graphics::Shutdown()
{
	if(d3D)
	{
		d3D->Shutdown();
		delete d3D;
		d3D = NULL;
	}

	// Release the camera object.
	if(camera)
	{
		delete camera;
		camera = 0;
	}
}