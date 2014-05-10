#include "includes.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "Input.h"
using namespace e;

GameWorld::GameWorld(ID3D11Device *device, e::XMVECTOR pos)
	:playerBullets(device, RM::Get().GetModel(RM::MODEL_PLAYER), RM::Get().GetShader<ColorInstancedShader>(), 100, 0.01f, e::XMFLOAT2(0.0f, 1.0f), GAME_EVENT_PLAYER_BULLET_CREATE),
	collider(),
	enemies(device, pos, 10.0f, size.x, 8),
	difficulty(0)
{
	auto &rm = RM::Get();
	player = make_shared<ColorDrawableEntity>(rm.GetModel(RM::MODEL_PLAYER), rm.GetShader<ColorShader>(), e::make_shared<GameEntity>(pos - e::XMVectorSet(0.0f, size.y / 2.0f, 0.0f, 0.0f), 100, 100, 0.02f, rm.GetModel(RM::MODEL_PLAYER).GetSize(), Gun::PlayerGun(500)), e::XMFLOAT4(0.0f, 1.0f, 0.3f, 1.0f));
	XMStoreFloat3(&this->pos, pos);
	collider.InsertFirst(player->GetEntity());

	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_HEALTH_SET, e::bind(&GameEntity::SetHealth, player->GetEntity().get(), e::placeholders::_1)));
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_MAX_HEALTH_SET, e::bind(&GameEntity::SetMaxHealth, player->GetEntity().get(), e::placeholders::_1)));
}

void GameWorld::Loop(InputType input, int frame)
{
	auto off = e::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	auto playerEntity = player->GetEntity();
	if (input[Input::ACTION_LEFT] && playerEntity->GetPos().x > pos.x - size.x / 2.0f)
		off += e::XMVectorSet(playerEntity->GetSpeed() * -frame, 0.0f, 0.0f, 0.0f);
	if (input[Input::ACTION_RIGHT] && playerEntity->GetPos().x < pos.x + size.x / 2.0f)
		off += e::XMVectorSet(playerEntity->GetSpeed() * frame, 0.0f, 0.0f, 0.0f);
	if (input[Input::ACTION_FIRE])
		playerEntity->Fire();
	collider.Update();
	playerBullets.Loop(frame);
	playerEntity->MoveBy(off);
	enemies.Loop(frame);
}

void GameWorld::Render(const RenderParams &params)
{
	player->Render(params);
	enemies.Render(params);
	playerBullets.Render(params);
}


void GameWorld::OnEnemyDeath(const e::shared_ptr<GameEntity> enemy)
{
	difficulty++;
}

e::unordered_map<int, int> GameWorld::GetPlayerData()
{
	e::unordered_map<int, int> ret;
	ret[UPGRADE_EVENT_HEALTH_SET] = player->GetEntity()->GetHealth();
	ret[UPGRADE_EVENT_MAX_HEALTH_SET] = player->GetEntity()->GetMaxHealth();
	return ret;
}