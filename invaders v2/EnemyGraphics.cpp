#include "EnemyGraphics.h"


EnemyGraphics::EnemyGraphics(void)
{
}


EnemyGraphics::~EnemyGraphics(void)
{
}

bool EnemyGraphics::Update(ID3D11DeviceContext* context)
{
	shared_ptr<Entity> enemy = world->GetEnemies()->GetEnemy(ind);
	if(enemy->IsDead())
		return false;
	pos = enemy->GetPos();

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);
	D3DXMatrixTranspose(&moveMatrix, &moveMatrix);

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, &moveMatrix, sizeof(moveMatrix));

	context->Unmap(matrixBuffer, 0);
	return true;
}