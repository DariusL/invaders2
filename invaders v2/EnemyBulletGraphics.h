#pragma once
#include "bulletgraphics.h"
class EnemyBulletGraphics :
	public BulletGraphics
{
public:
	EnemyBulletGraphics(void);
	~EnemyBulletGraphics(void);

	bool Update(ID3D11DeviceContext *context);
};

