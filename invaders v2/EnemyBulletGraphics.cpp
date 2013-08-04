#include "EnemyBulletGraphics.h"


EnemyBulletGraphics::EnemyBulletGraphics(void)
{
}


EnemyBulletGraphics::~EnemyBulletGraphics(void)
{
}


bool EnemyBulletGraphics::Update(ID3D11DeviceContext *context)
{
	list<Entity> bullets = world->GetEnemies()->getBullets();

	bulletCount = bullets.size();

	if(bulletCount == 0)
		return false;

	int i = 0;

	for(auto &x : bullets)
	{
		if(i >= MAX_BULLET_COUNT)
			break;
		bulletData[i] = x.GetPos();
		i++;
	}
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(vertexBuffers[1], 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, bulletData.get(), sizeof(D3DXVECTOR3) * bulletCount);

	context->Unmap(vertexBuffers[1], 0);

	return true;
}