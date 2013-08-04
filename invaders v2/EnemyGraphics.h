#pragma once
#include "playergraphics.h"
class EnemyGraphics : public PlayerGraphics
{
	int ind;
public:
	EnemyGraphics(void);
	~EnemyGraphics(void);

	void setIndex(int i){ind = i;}
	bool Update(ID3D11DeviceContext*);
};

