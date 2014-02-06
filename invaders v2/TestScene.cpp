#include "includes.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "StringPool.h"

TestScene::TestScene()
:Screen(e::XMLoadFloat3(&ZeroVec3))
{
	stuff.emplace_back(new SimpleDrawableEntity(ZeroVec3, SP::Get().GetString("TEXT"), RM::Get().GetShader<ColorShader>()));
	stuff.emplace_back(new SimpleDrawableEntity(e::XMVectorSet(0.0f, -2.0f, 0.0f, 0.0f), SP::Get().GetString("MORE TEXT"), RM::Get().GetShader<ColorShader>()));
	stuff.emplace_back(new SimpleDrawableEntity(e::XMVectorSet(0.0f, -4.0f, 0.0f, 0.0f), SP::Get().GetString("MORE TEXT"), RM::Get().GetShader<ColorShader>()));
}

int TestScene::Loop(int input, float frameLength)
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

	float x = 0.0f,
		y = 0.0f,
		z = 0.0f;
	frameLength *= 10;
	if (input & ControlCodes::MOVE_UP)
		y += frameLength;
	if (input & ControlCodes::MOVE_DOWN)
		y -= frameLength;
	if (input & ControlCodes::MOVE_LEFT)
		x -= frameLength;
	if (input & ControlCodes::MOVE_RIGHT)
		x += frameLength;
	if (input & ControlCodes::MOVE_FORWARD)
		z += frameLength;
	if (input & ControlCodes::MOVE_BACK)
		z -= frameLength;

	camera.Move(x, y, z);

	return RESULT_CONTINUE;
}

void TestScene::Render(const RenderParams &params)
{
	for (auto &o : stuff)
		o->Render(params);
}