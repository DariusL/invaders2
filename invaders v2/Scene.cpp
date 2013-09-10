#include "Scene.h"


Scene::Scene(void)
{
}


Scene::~Scene(void)
{
}

bool Scene::Start(shared_ptr<Level> level)
{
	return true;
}

void Scene::Stop()
{
}

int Scene::OnLoop(int input, float frameLength)
{
	return IWorld::Result::CONTINUE;
}



bool Scene::Init(ComPtr<ID3D11Device>)
{
	return true;
}

void Scene::Render(RenderParams)
{
}