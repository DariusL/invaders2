#include "includes.h"
#include "BulletList.h"
#include "Observers.h"

BulletList::BulletList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, float speed, e::XMFLOAT2 dir, int spawnEvent, e::XMFLOAT4 color)
:GameEntityList(device, model, shader, maxObjectCount, color), speed(speed), dir(dir)
{
	or = GameObservers::Register(spawnEvent, e::bind(&BulletList::Add, this, e::placeholders::_1));
}

void BulletList::Loop(int frame)
{
	using namespace e;
	GameEntityList::Loop(frame);
	auto vec = e::XMLoadFloat2(&dir) * (speed * frame);
	for (auto &enemy : enemies)
		enemy->MoveBy(vec);
}