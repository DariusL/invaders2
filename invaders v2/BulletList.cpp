#include "includes.h"
#include "BulletList.h"
#include "Observers.h"

BulletList::BulletList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, e::XMFLOAT2 dir, int spawnEvent)
:GameEntityList(device, model, shader, maxObjectCount), dir(dir)
{
	or = GameObservers::Register(spawnEvent, e::bind(&BulletList::Add, this, e::placeholders::_1));
}

void BulletList::Loop(int frame)
{
	using namespace e;
	GameEntityList::Loop(frame);
	auto dir = e::XMLoadFloat2(&this->dir);
	for (auto &enemy : enemies)
	{
		auto vec = dir * (enemy->GetSpeed() * frame);
		enemy->MoveBy(vec);
	}
}