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

	Model playerModel;

	playerModel.vertexCount = 4;
	playerModel.vertices = new VertexType[playerModel.vertexCount];
	playerModel.indexCount = 6;
	playerModel.indices = new int[playerModel.indexCount];	
	
	playerModel.vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	playerModel.vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	playerModel.vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left
	playerModel.vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	playerModel.vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	playerModel.vertices[2].color = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);

	playerModel.vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	playerModel.vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	playerModel.indices[0] = 1;
	playerModel.indices[1] = 2;
	playerModel.indices[2] = 0;

	playerModel.indices[3] = 1;
	playerModel.indices[4] = 3;
	playerModel.indices[5] = 2;

	mainObject = new PlayerGraphics();

	mainObject->SetPos(D3DXVECTOR3(0, -5, 0));
	mainObject->SetModel(playerModel);

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