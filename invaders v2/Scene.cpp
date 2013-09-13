#include "Scene.h"
#include "App.h"
#include "ResourceManager.h"
#include "Model.h"

Scene::Scene(void)
{
	started = false;
	r = 50.0f;
	camera.SetTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	camera.SetPosition(D3DXVECTOR3(0.0f, -30.0f, -30.0f));
	xz = 0.0f;
	yz = 0.0f;
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
	if(input & ControlCodes::DOWN)
		yz -= frameLength;
	if(input & ControlCodes::UP)
		yz += frameLength;
	if(yz < 0.0f)
		yz += 360.0f;
	if(yz > 360.0f)
		yz -= 360.0f;

	return IWorld::Result::CONTINUE;
}


bool Scene::Init(ComPtr<ID3D11Device> device)
{
	ResourceManager *rm = App::Get()->GetResourceManager();
	for(int i = 0; i < 5; i++)
	{
		random.push_back(make_shared<DrawableEntity>(D3DXVECTOR3(i * 10.0f - 20, 0.0f, 0.0f), rm->GetNormalModel()));
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