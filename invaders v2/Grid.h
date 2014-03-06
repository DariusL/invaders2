#pragma once
#include "includes.h"
#include "IDrawable.h"
#include "GameEntityList.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Movement.h"
#include "Collider.h"

class Grid : public IDrawable
{
private:
	enum DIR
	{
		LEFT,
		RIGHT
	};
	e::unordered_map<int, e::unique_ptr<GameEntityList>> instancers;
	int time;
	int lastDrop;
	int dropFreq;
	float worldWidth;
	float width;
	const float downOff;
	int columnCount;
	DIR dir;
	Movement movement;
	e::XMFLOAT3 first;
	Collider &collider;
	void AddRow();
public:
	Grid(ID3D11Device *device, e::XMVECTOR pos, float width, float worldWidth, int columnCount, Collider &collider);
	void Render(const RenderParams &params);
	void Loop(int frame);
	void MoveTo(e::XMVECTOR pos);
};