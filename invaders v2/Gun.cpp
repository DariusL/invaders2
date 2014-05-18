#include "includes.h"
#include "Gun.h"
#include "Observers.h"
#include "ResourceManager.h"

Gun::Gun(int spawnEvent, uint firePeriod, float off, int damage, ColorModel &model)
	:spawnEvent(spawnEvent), firePeriod(firePeriod), lastFired(0), bulletSize(model.GetSize()), off(off), bulletSpeed(1.0f / firePeriod * 50.0f), damage(damage)
{
}

void Gun::Fire(e::XMVECTOR gunPos)
{
 	uint now = clock();
	if (lastFired + firePeriod <= now)
	{
		lastFired = now;
		GameObservers::Notify(spawnEvent, e::make_shared<GameEntity>(gunPos + Utils::VectorSet(0.0f, off), 1, damage, bulletSpeed, bulletSize, nullptr, e::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
	}
}


e::unique_ptr<Gun> Gun::PlayerGun(uint firePeriod, int damage)
{
	return make_unique<Gun>(GAME_EVENT_PLAYER_BULLET_CREATE, firePeriod, 1.0f, damage, RM::Get().GetModel(RM::MODEL_PLAYER));
}

e::unique_ptr<Gun> Gun::EnemyGun(uint firePeriod, int damage)
{
	return make_unique<Gun>(GAME_EVENT_ENEMY_BULLET_CREATE, firePeriod, -1.0f, damage, RM::Get().GetModel(RM::MODEL_PLAYER));
}