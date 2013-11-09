#include "includes.h"
#include "Scene.h"
#include "App.h"
#include "ResourceManager.h"
#include "Model.h"
#include "WaterShader.h"

Scene::Scene(void)
:gabenizer(DefVec3, DefVec3, RM::Get().GetTexturedModel(RM::TexturedModels::INV_BOX), RM::Get().GetShader<TextureShader>(),
	ResourceManager::Get().GetTexture(RM::Textures::TEXTURE_GABEN), D3DXVECTOR3(400.0f, 400.0f, 400.0f)),

light(DefVec3, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), RM::Get().GetModel(RM::Models::MODEL_BALL), RM::Get().GetShader<ColorShader>()),

bumpy(D3DXVECTOR3(0.0f, 0.0f, -5.0f), RM::Get().GetNormalMappedModel(), RM::Get().GetShader<NormalMappedShader>())
{
	camera.Move(0.0f, -10.0f, -50.0f);
	started = false;
	cameras.emplace_back(D3DXVECTOR3(0.0f, 0.0f, -50.0f), DefVec3, D3DXVECTOR3(0.0f, -5.0f, 0.0f), DefVec3,
		ResourceManager::Get().GetTexturedModel(RM::TexturedModels::PLANE), RM::Get().GetShader<TextureShader>(), 400, 200, 20.0f, 10.0f);
	mirrors.emplace_back(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, 0.0f), RM::Get().GetTexturedModel(RM::TexturedModels::PLANE),
		RM::Get().GetShader<MirrorShader>(), 800, 800, 20.0f, 20.0f);
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
	float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
	if (input & ControlCodes::LEFT)
		yaw -= frameLength;
	if (input & ControlCodes::RIGHT)
		yaw += frameLength;
	if (input & ControlCodes::DOWN)
		pitch += frameLength;
	if (input & ControlCodes::UP)
		pitch -= frameLength;
	if (input & ControlCodes::ROLL_LEFT)
		roll += frameLength;
	if (input & ControlCodes::ROLL_RIGHT)
		roll -= frameLength;
	if (yaw != 0.0f)
		camera.Yaw(yaw);
	if (pitch != 0.0f)
		camera.Pitch(pitch);
	if (roll != 0.0f)
		camera.Roll(roll);

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

void Scene::Init(ComPtr<ID3D11Device> device)
{
	ResourceManager *rm = App::Get()->GetResourceManager();
	light.Init(device);
	bumpy.Init(device);
	for (auto &mirror : mirrors)
		mirror.Init(device);
	for (auto &camera : cameras)
		camera.Init(device);
	gabenizer.Init(device);
}

void Scene::Render(const RenderParams &params)
{
	//light.Render(params);
	//bumpy.Render(params);
	gabenizer.Render(params);
}