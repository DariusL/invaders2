#include "includes.h"
#include "Scene.h"
#include "App.h"
#include "ResourceManager.h"
#include "Model.h"
#include "WaterShader.h"

Scene::Scene(void)
:remoteCamera(D3DXVECTOR3(-30.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -5.0f, 0.0f),
	ResourceManager::Get().GetTexturedModel(ResourceManager::TexturedModels::PLANE), ResourceManager::Get().GetShader<TextureShader>(), 20, 10),

	gabenizer(DefVec3, ResourceManager::Get().GetTexturedModel(ResourceManager::TexturedModels::INV_BOX), ResourceManager::Get().GetShader<TextureShader>(),
	ResourceManager::Get().GetTexture(ResourceManager::Textures::TEXTURE_GABEN), D3DXVECTOR3(100.0f, 100.0f, 100.0f))
{
	camera.Forward(-30);
	started = false;
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
	float yaw = 0.0f, pitch = 0.0f;
	if (input & ControlCodes::LEFT)
		yaw -= frameLength;
	if (input & ControlCodes::RIGHT)
		yaw += frameLength;
	if (input & ControlCodes::DOWN)
		pitch += frameLength;
	if (input & ControlCodes::UP)
		pitch -= frameLength;
	if (yaw != 0)
		camera.Yaw(yaw);
	if (pitch != 0)
		camera.Pitch(pitch);

	auto move = DefVec3;
	frameLength *= 10;
	if (input & ControlCodes::MOVE_UP)
		move.y += frameLength;
	if (input & ControlCodes::MOVE_DOWN)
		move.y -= frameLength;
	if (input & ControlCodes::MOVE_LEFT)
		move.x -= frameLength;
	if (input & ControlCodes::MOVE_RIGHT)
		move.x += frameLength;
	if (input & ControlCodes::MOVE_FORWARD)
		move.z += frameLength;
	if (input & ControlCodes::MOVE_BACK)
		move.z -= frameLength;

	camera.Forward(move.z);
	camera.Up(move.y);
	camera.Right(move.x);
	
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