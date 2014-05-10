#pragma once
#include "includes.h"
#include "IDrawable.h"
#include "EnemyList.h"
#include "GameEntity.h"
#include "ResourceManager.h"
#include "Movement.h"
#include "BulletList.h"

class Grid : public IDrawable
{
private:
	enum DIR
	{
		LEFT,
		RIGHT
	};
	e::unordered_map<int, e::unique_ptr<EnemyList>> instancers;
	int time;
	int lastDrop;
	int dropFreq;
	float worldWidth;
	float width;
	const float downOff;
	uint columnCount;
	DIR dir;
	Movement movement;
	e::XMFLOAT3 first;
	void AddRow();
	e::default_random_engine generator;
	BulletList bullets;
public:
	Grid(ID3D11Device *device, e::XMVECTOR pos, float width, float worldWidth, uint columnCount);
	void Render(RenderParams &params);
	void Loop(int frame);
	void MoveTo(e::XMVECTOR pos);
private:
	void Fire(int frame);
};