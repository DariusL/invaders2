#include "Scene.h"
#include "App.h"
#include "ResourceManager.h"
#include "Model.h"

Scene::Scene(void)
{
	started = false;
	
	camera.SetTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	camera.SetPosition(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
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
	for(int i = 0; i < 20; i++)
	{
		random.push_back(make_shared<DrawableEntity>(D3DXVECTOR3(i * 5.0f - 50, 0.0f, 0.0f), rm->GetNormalModel()));
		if(!random[i]->Init(device))
			return false;
	}
	return true;
}

void Scene::Render(RenderParams params)
{
	for(auto &a : random)
		a->Render(params);
}