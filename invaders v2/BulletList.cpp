#include "includes.h"
#include "BulletList.h"
using namespace e;

void BulletList::Loop(int frame)
{
	auto vec = e::XMLoadFloat2(&dir) * (speed * frame);
	for (auto &enemy : enemies)
		enemy->MoveBy(vec);
}