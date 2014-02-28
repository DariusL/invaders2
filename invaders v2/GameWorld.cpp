#include "includes.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "Input.h"

GameWorld::GameWorld(ID3D11Device *device, e::XMVECTOR pos)
:player(pos - e::XMVectorSet(0.0f, size.y / 2.0f, 0.0f, 0.0f), RM::Get().GetModel(RM::MODEL_PLAYER), RM::Get().GetShader<ColorShader>(), 0.2f, 10.0f, e::XMFLOAT4(0.0f, 1.0f, 0.3f, 1.0f)),
enemies(device, pos, 10.0f, size.x, 8)
{
	XMStoreFloat3(&this->pos, pos);
}

void GameWorld::Loop(float frame)
{
	auto off = e::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	if (Input::IsKeyDown(KEYS_LEFT) && player.GetPos().x > pos.x - size.x / 2.0f)
		off += e::XMVectorSet(player.GetSpeed() * -frame, 0.0f, 0.0f, 0.0f);
	if (Input::IsKeyDown(KEYS_RIGHT) && player.GetPos().x < pos.x + size.x / 2.0f)
		off += e::XMVectorSet(player.GetSpeed() * frame, 0.0f, 0.0f, 0.0f);
	player.MoveBy(off);
	enemies.Loop(frame);
}

void GameWorld::Render(const RenderParams &params)
{
	player.Render(params);
	enemies.Render(params);
}