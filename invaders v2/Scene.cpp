#include "includes.h"
#include "Scene.h"
#include "App.h"
#include "ResourceManager.h"
#include "Model.h"
#include "WaterShader.h"

Scene::Scene(void)
{
	started = false;
	camera.Forward(-30.0f);
	camera.Up(-10.0f);
	camera.Pitch(1.0f);
}


Scene::~Scene(void)
{
}

bool Scene::Start(shared_ptr<Level> level)
{
	started = true;
	return true;
}

void Scene::Stop()
{
	started = false;
}

int Scene::OnLoop(int input, float frameLength)
{
	return IWorld::Result::CONTINUE;
}


bool Scene::Init(ComPtr<ID3D11Device> device)
{
	ResourceManager *rm = App::Get()->GetResourceManager();
	light = make_shared<Light>(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), rm->GetModel(ResourceManager::Models::MODEL_BALL), rm->GetShader<ColorShader>());
	light->Init(device);
	bumpy = make_shared<DrawableBumpyEntity>(D3DXVECTOR3(0.0f, 0.0f, -5.0f), rm->GetTexturedModel(), rm->GetShader<NormalMappedShader>());
	bumpy->Init(device);
	water = make_shared<WaterPlane>(D3DXVECTOR3(0.0f, 0.0f, 0.0f), rm->GetPlane(), rm->GetShader<WaterShader>());
	water->Init(device);
	return true;
}

void Scene::Render(const RenderParams &params)
{
	light->Render(params);
	bumpy->Render(params);
}