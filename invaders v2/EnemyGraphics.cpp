#include "EnemyGraphics.h"


EnemyGraphics::EnemyGraphics(void)
{
}


EnemyGraphics::~EnemyGraphics(void)
{
}

void EnemyGraphics::Update(ID3D11DeviceContext* context)
{
	pos = world->GetEnemies()->GetEnemy(ind)->getPos();

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);
	D3DXMatrixTranspose(&moveMatrix, &moveMatrix);

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, &moveMatrix, sizeof(moveMatrix));

	context->Unmap(matrixBuffer, 0);
}