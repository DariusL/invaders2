#include "includes.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "StringPool.h"

TestScene::TestScene()
:Screen(e::XMLoadFloat3(&ZeroVec3))
{
	stuff.emplace_back(new SimpleDrawableEntity(e::XMLoadFloat3(&ZeroVec3), SP::Get().GetString("TEXT"), RM::Get().GetShader<ColorShader>()));
	stuff.emplace_back(new SimpleDrawableEntity(e::XMVectorSet(0.0f, -2.0f, 0.0f, 0.0f), SP::Get().GetString("MORE TEXT"), RM::Get().GetShader<ColorShader>()));
	stuff.emplace_back(new SimpleDrawableEntity(e::XMVectorSet(0.0f, -4.0f, 0.0f, 0.0f), SP::Get().GetString("MORE TEXT"), RM::Get().GetShader<ColorShader>()));
}

int TestScene::Loop(int input, int frameLength)
{
	float frame = frameLength / 100.0f;
	float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
	if (input & ControlCodes::LEFT)
		yaw -= frame;
	if (input & ControlCodes::RIGHT)
		yaw += frame;
	if (input & ControlCodes::DOWN)
		pitch += frame;
	if (input & ControlCodes::UP)
		pitch -= frame;
	if (input & ControlCodes::ROLL_LEFT)
		roll -= frame;
	if (input & ControlCodes::ROLL_RIGHT)
		roll += frame;
	if (yaw != 0.0f)
		camera.Yaw(yaw);
	if (pitch != 0.0f)
		camera.Pitch(pitch);
	if (roll != 0.0f)
		camera.Roll(roll);

	float x = 0.0f,
		y = 0.0f,
		z = 0.0f;
	if (input & ControlCodes::MOVE_UP)
		y += frame;
	if (input & ControlCodes::MOVE_DOWN)
		y -= frame;
	if (input & ControlCodes::MOVE_LEFT)
		x -= frame;
	if (input & ControlCodes::MOVE_RIGHT)
		x += frame;
	if (input & ControlCodes::MOVE_FORWARD)
		z += frame;
	if (input & ControlCodes::MOVE_BACK)
		z -= frame;

	camera.Move(x, y, z);

	return RESULT_CONTINUE;
}

void TestScene::Render(const RenderParams &params)
{
	for (auto &o : stuff)
		o->Render(params);
}