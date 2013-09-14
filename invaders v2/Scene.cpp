#include "Scene.h"
#include "App.h"
#include "ResourceManager.h"
#include "Model.h"

Scene::Scene(void)
{
	started = false;
	r = 50.0f;
	yaw = 0.0f;
	pitch = 0.2f;
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
		pitch -= frameLength;
	if(input & ControlCodes::UP)
		pitch += frameLength;
	if(input & ControlCodes::LEFT)
		yaw += frameLength;
	if(input & ControlCodes::RIGHT)
		yaw -= frameLength;
	if(input & ControlCodes::PLUS)
		r -= frameLength * 10;
	if(input & ControlCodes::MINUS)
		r += frameLength * 10;
	if(input & ControlCodes::FIRE)
	{
		for(auto &a : random)
			a->SwapShader();
	}
	
	camera.SetRotation(yaw, pitch, r);
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