#include "includes.h"
#include "TestScene.h"


TestScene::TestScene()
{
}

int TestScene::OnLoop(int input, float frameLength)
{
	return IWorld::Result::CONTINUE;
}

void TestScene::Render(RenderParams &params)
{

}

void TestScene::Init(ComPtr<ID3D11DeviceContext> context)
{

}