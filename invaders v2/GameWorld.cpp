#include "includes.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "Input.h"

GameWorld::GameWorld(e::XMVECTOR pos)
:player(pos, RM::Get().GetModel(RM::MODEL_PLANE), RM::Get().GetShader<ColorShader>(), e::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f))
{

}

void GameWorld::Loop(float frame)
{
	auto off = e::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	if (Input::IsKeyDown(KEYS_LEFT))
		off += e::XMVectorSet(-10.0f * frame, 0.0f, 0.0f, 0.0f);
	if (Input::IsKeyDown(KEYS_RIGHT))
		off += e::XMVectorSet(10.0f * frame, 0.0f, 0.0f, 0.0f);
	player.MoveBy(off);
}

void GameWorld::Render(const RenderParams &params)
{
	player.Render(params);
}