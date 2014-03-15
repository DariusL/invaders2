#include "includes.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "Input.h"
using namespace e;

GameWorld::GameWorld(ID3D11Device *device, e::XMVECTOR pos)
:player(make_shared<ColorDrawableEntity>(pos - e::XMVectorSet(0.0f, size.y / 2.0f, 0.0f, 0.0f), 500, 0.02f, 10, 100, RM::Get().GetModel(RM::MODEL_PLAYER), RM::Get().GetShader<ColorShader>(), e::XMFLOAT4(0.0f, 1.0f, 0.3f, 1.0f))),
playerBullets(device, RM::Get().GetModel(RM::MODEL_PLAYER), RM::Get().GetShader<ColorInstancedShader>(), 100, 0.01f, e::XMFLOAT2(0.0f, 1.0f)),
collider(),
enemies(device, pos, 10.0f, size.x, 8, collider)
{
	XMStoreFloat3(&this->pos, pos);
	collider.InsertFirst(player);
}

void GameWorld::Loop(int frame)
{
	auto off = e::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	if (Input::IsKeyDown(KEYS_LEFT) && player->GetPos().x > pos.x - size.x / 2.0f)
		off += e::XMVectorSet(player->GetSpeed() * -frame, 0.0f, 0.0f, 0.0f);
	if (Input::IsKeyDown(KEYS_RIGHT) && player->GetPos().x < pos.x + size.x / 2.0f)
		off += e::XMVectorSet(player->GetSpeed() * frame, 0.0f, 0.0f, 0.0f);
	if (Input::IsKeyDown(KEYS_FIRE))
		if (player->Fire())
		{
			auto pos = player->GetPos();
			auto bullet = make_shared<GameEntity>(e::XMLoadFloat3(&pos) + Utils::VectorSet(0.0f, 1.0f), RM::Get().GetModel(RM::MODEL_PLAYER).GetSize(), 1, 10);
			playerBullets.Add(bullet);
			collider.InsertFirst(bullet);
		}
	collider.Update();
	playerBullets.Loop(frame);
	player->MoveBy(off);
	enemies.Loop(frame);
}

void GameWorld::Render(const RenderParams &params)
{
	player->Render(params);
	enemies.Render(params);
	playerBullets.Render(params);
}