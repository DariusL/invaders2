#pragma once
#include "AbstractGroupGraphics.h"
#include "EnemyGraphics.h"

class EnemyGridGraphics : public AbstractGroupGraphics
{
	vector<shared_ptr<EnemyGraphics>> enemyGraphics;
public:
	bool Init(ID3D11Device*, World*, HWND);
	void Shutdown();
	void Render(ID3D11DeviceContext*, D3DXMATRIX);
public:
	EnemyGridGraphics(void);
	~EnemyGridGraphics(void);
};

