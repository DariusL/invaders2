#include "includes.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "StringPool.h"

TestScene::TestScene()
{
	camera.Move(0.0f, 0.0f, -10.0f);
	stuff.emplace_back(new SimpleDrawableEntity(ZeroVec3, SP::Get().GetString("TEXT"), RM::Get().GetShader<ColorShader>()));
	stuff.emplace_back(new SimpleDrawableEntity(XMFLOAT3(0.0f, -2.0f, 0.0f), SP::Get().GetString("MORE TEXT"), RM::Get().GetShader<ColorShader>()));
	stuff.emplace_back(new SimpleDrawableEntity(XMFLOAT3(0.0f, -4.0f, 0.0f), SP::Get().GetString("MORE TEXT"), RM::Get().GetShader<ColorShader>()));
}

int TestScene::OnLoop(int input, float frameLength)
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
		roll -= frameLength;
	if (input & ControlCodes::ROLL_RIGHT)
		roll += frameLength;
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

	camera.Move(move);

	return IWorld::Result::CONTINUE;
}

void TestScene::Render(RenderParams &params)
{
	for (auto &o : stuff)
		o->Render(params);
}