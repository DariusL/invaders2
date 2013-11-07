#include "includes.h"
#include "Scene.h"
#include "App.h"
#include "ResourceManager.h"
#include "Model.h"
#include "WaterShader.h"

Scene::Scene(void)
:remoteCamera(D3DXVECTOR3(-30.0f, -10.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -5.0f, 0.0f),
	ResourceManager::Get().GetTexturedModel(ResourceManager::TexturedModels::PLANE), ResourceManager::Get().GetShader<TextureShader>(), 20, 10),

	gabenizer(DefVec3, ResourceManager::Get().GetTexturedModel(ResourceManager::TexturedModels::INV_BOX), ResourceManager::Get().GetShader<TextureShader>(),
	ResourceManager::Get().GetTexture(ResourceManager::Textures::TEXTURE_GABEN), D3DXVECTOR3(10.0f, 10.0f, 10.0f))
{
	started = false;
	camera.Forward(-30.0f);
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
	bumpy = make_shared<DrawableBumpyEntity>(D3DXVECTOR3(0.0f, 0.0f, -5.0f), rm->GetNormalMappedModel(), rm->GetShader<NormalMappedShader>());
	bumpy->Init(device);
	remoteCamera.Init(device);
	gabenizer.Init(device);
	return true;
}

void Scene::Render(const RenderParams &params)
{
	//light->Render(params);
	//bumpy->Render(params);
	gabenizer.Render(params);
}