#include "includes.h"
#include "TestScene.h"
#include "ResourceManager.h"

TestScene::TestScene()
:thing(ZeroVec3, RM::Get().GetModel(RM::MODEL_PLANE), RM::Get().GetShader<ColorShader>())
{
	camera.Move(0.0f, 0.0f, 10.0f);
}

int TestScene::OnLoop(int input, float frameLength)
{
	return IWorld::Result::CONTINUE;
}

void TestScene::Render(RenderParams &params)
{
	thing.Render(params);
}