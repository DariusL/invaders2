#include "includes.h"
#include "BulletList.h"
#include "Observers.h"
using namespace e;

BulletList::BulletList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, float speed, e::XMFLOAT2 dir, int spawnEvent)
:GameEntityList(device, model, shader, maxObjectCount), speed(speed), dir(dir)
{
	Observers::Register(spawnEvent, e::bind(&BulletList::Add, this, e::placeholders::_1));
}

void BulletList::Loop(int frame)
{
	GameEntityList::Loop(frame);
	auto vec = e::XMLoadFloat2(&dir) * (speed * frame);
	for (auto &enemy : enemies)
		enemy->MoveBy(vec);
}