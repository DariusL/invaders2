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

	//isvalomi buferiai, nuspalvinamas fonas
	d3D.BeginScene();

	//is scenos gaunama kamera ir sviesa
	Camera &camera = world->GetCamera();
	camera.Render();
	shared_ptr<Light> light = world->GetLight();

	camera.GetViewMatrix(viewMatrix);
	d3D.GetProjectionMatrix(projectionMatrix);
	//transformacijos matrica is pasaulio erdves i ekrano erdve
	D3DXMatrixMultiply(&transMatrix, &viewMatrix, &projectionMatrix);

	//renderinimo informacijos struktura
	RenderParams params;
	params.brightness = brightness;//foninio apsvietimo stiprumas
	params.context = d3D.GetDeviceContext();//kontekstas
	params.transMatrix = transMatrix;//transformacijos matrica
	params.lightPos = light->GetPos();//sviesos pozicija pasaulio erdveje
	params.diffuseColor = light->GetColor();//difuzines sviesos spalva
	params.cameraPos = camera.GetPosition();//kameros pozicija pasaulio erdveje

	//visi grafiniai objektai sudaro medi, kurio virsus yra scena
	world->Render(params);

	//vaizdas perduodamas i ekrana
	d3D.EndScene();
}