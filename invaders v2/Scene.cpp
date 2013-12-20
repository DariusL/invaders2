#include "includes.h"
#include "Scene.h"
#include "App.h"
#include "ResourceManager.h"
#include "Model.h"
#include "WaterShader.h"
#include "InstancedTextureShader.h"

Scene::Scene(ComPtr<ID3D11Device> device)
:gabenizer( ZeroVec3, ZeroVec3, RM::Get().GetNormalTexturedModel(RM::NORMAL_TEXTURED_MODEL_INV_BOX), RM::Get().GetShader<ShadowShader>(),
RM::Get().GetTexture(RM::TEXTURE_GABEN), XMFLOAT3(800.0f, 800.0f, 1000.0f)),

light(device, XMFLOAT3(0.0f, -80.0f, -30.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), RM::Get().GetModel(RM::MODEL_BALL), RM::Get().GetShader<ColorShader>(), 800, 800),

water(device, XMFLOAT3(0.0f, -145.0f, 0.0f), XMFLOAT3(XM_PIDIV2, 0.0f, 0.0f), RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
RM::Get().GetShader<WaterShader>(), 300, 300, 30.0f, 30.0f, RM::Get().GetTexture(RM::TEXTURE_WATER_NORMAL_MAP)),

bath(XMFLOAT3(0.0f, -150.0f, 0.0f), ZeroVec3, RM::Get().GetNormalTexturedModel(RM::NORMAL_TEXTURED_MODEL_BATH),
RM::Get().GetShader<ShadowShader>(), RM::Get().GetTexture(RM::TEXTURE_WALL), XMFLOAT3(50.0f, 10.0f, 50.0f)),

billboard(XMFLOAT3(0.0f, -300.0f, 200.0f), RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE), RM::Get().GetShader<TextureShader>(),
RM::Get().GetTexture(RM::TEXTURE_TREE), XMFLOAT3(10.0f, 10.0f, 1.0f)),

billboard2(XMFLOAT3(30.0f, -300.0f, 200.0f), RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE), RM::Get().GetShader<TextureShader>(),
RM::Get().GetTexture(RM::TEXTURE_TREE), XMFLOAT3(10.0f, 10.0f, 1.0f)),

ground(XMFLOAT3(0.0f, -300.0f, 0.0f), XMFLOAT3(XM_PIDIV2, 0.0f, 0.0f), RM::Get().GetNormalTexturedModel(RM::NORMAL_TEXTURED_MODEL_PLANE),
RM::Get().GetShader<ShadowShader>(), RM::Get().GetTexture(RM::TEXTURE_WALL), XMFLOAT3(600.0f, 600.0f, 1.0f)),

wall(XMFLOAT3(0.0f, 0.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), RM::Get().GetNormalTexturedModel(RM::NORMAL_TEXTURED_MODEL_PLANE),
RM::Get().GetShader<ShadowShader>(), RM::Get().GetTexture(RM::TEXTURE_WALL), XMFLOAT3(200.0f, 200.0f, 1.0f)),

particles(device, RM::Get().GetModel(RM::MODEL_BALL), RM::Get().GetShader<ColorInstancedShader>(), 1000, XMFLOAT3(0.0f, -300.0f, -70.0f)),

thing(XMFLOAT3(0.0f, -130.0f, -10.0f), RM::Get().GetNormalMappedModel(), RM::Get().GetShader<NormalMappedShader>(), RM::Get().GetTexture(RM::TEXTURE_WATER_NORMAL_MAP))
{
	camera.Move(0.0f, -10.0f, -50.0f);
	started = false;
	cameras.reserve(2);
	cameras.emplace_back(device, XMFLOAT3(0.0f, -5.0f, -20.0f), ZeroVec3, XMFLOAT3(0.0f, -5.0f, 0.0f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		RM::Get().GetShader<TextureShader>(), 400, 200, 20.0f, 10.0f);

	cameras.emplace_back(device, XMFLOAT3(-20.0f, -5.0f, -20.0f), ZeroVec3, XMFLOAT3(-20.0f, -5.0f, 0.0f), ZeroVec3, RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
		RM::Get().GetShader<TextureShader>(), 400, 200, 20.0f, 10.0f);

	mirrors.emplace_back(device, XMFLOAT3(30.0f, -130.0f, 0.0f), XMFLOAT3(0.0f, XM_PIDIV2, 0.0f), RM::Get().GetTexturedModel(RM::TEXTURED_MODEL_PLANE),
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

	auto move = ZeroVec3;
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

	particles.OnLoop(frameLength);

	camera.Forward(move.z);
	camera.Up(move.y);
	camera.Right(move.x);
	
	return IWorld::Result::CONTINUE;
}

void Scene::Render(RenderParams &params)
{
	light.Render(params);
	gabenizer.Render(params);
	bath.Render(params);
	ground.Render(params);
	for (auto &mirror : mirrors)
		mirror.Render(params);
	water.Render(params);
	for (auto &remote : cameras)
		remote.Render(params);
	billboard.Render(params);
	billboard2.Render(params);
	particles.Render(params);
	thing.Render(params);
}


void Scene::GetRenderBalls(vector<MirrorBall*> &mirrorBalls, vector<RemoteCamera*> &cameraBalls)
{
	for (auto &mirror : mirrors)
		mirrorBalls.push_back(&mirror.GetRefletionBall());
	mirrorBalls.push_back(&water.GetRefletionBall());
	mirrorBalls.push_back(&water.GetRefractionBall());
	for (auto &camera : cameras)
		cameraBalls.push_back(&camera);
}