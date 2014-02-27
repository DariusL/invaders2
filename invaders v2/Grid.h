#pragma once
#include "includes.h"
#include "IDrawable.h"
#include "EnemyList.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Movement.h"

class Grid : public IDrawable, public Entity
{
	enum DIR
	{
		LEFT,
		RIGHT
	};
private:
	e::unordered_map<int, e::unique_ptr<EnemyList>> instancers;
	int time;
	float worldWidth;
	float width;
	const float downOff;
	int columnCount;
	DIR dir;
	Movement movement;
public:
	Grid(ID3D11Device *device, e::XMVECTOR pos, float width, float worldWidth, int columnCount);
	void Render(const RenderParams &params);
	void Loop(float frame);
	void MoveTo(e::XMVECTOR pos);
};