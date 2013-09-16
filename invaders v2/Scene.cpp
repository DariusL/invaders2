#include "includes.h"
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
	lightPitch = 0.0f;
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
	int shader = -1;
	if(input & ControlCodes::GLOBAL_DIFF)
		shader = ResourceManager::Shaders::GLOBAL_DIFFUSE;
	if(input & ControlCodes::GLOBAL_SPEC)
		shader = ResourceManager::Shaders::GLOBAL_SPECULAR;
	if(input & ControlCodes::POINT_DIFF)
		shader = ResourceManager::Shaders::POINT_DIFFUSE;
	if(input & ControlCodes::POINT_SPEC)
		shader = ResourceManager::Shaders::POINT_SPECULAR;
	if(shader != -1)
	{
		if(shader == ResourceManager::Shaders::GLOBAL_DIFFUSE || shader == ResourceManager::Shaders::GLOBAL_SPECULAR)
			light->Kill();
		else
			light->Revive();
		for(auto &a : random)
			a->SetShader(shader);
	}
	camera.SetRotation(yaw, pitch, r);
	lightPitch += frameLength;
	light->SetPos(lightPitch, 10.0f);
	return IWorld::Result::CONTINUE;
}


bool Scene::Init(ComPtr<ID3D11Device> device)
{
	ResourceManager *rm = App::Get()->GetResourceManager();
	light = make_shared<Light>(D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	light->Init(device);
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
	light->Render(params);
}