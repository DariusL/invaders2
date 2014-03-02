#pragma once
#include "includes.h"
#include "IDrawable.h"
#include "GameEntityList.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Movement.h"

class Grid : public IDrawable
{
	enum DIR
	{
		LEFT,
		RIGHT
	};
private:
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

	void AddRow();
public:
	Grid(ID3D11Device *device, e::XMVECTOR pos, float width, float worldWidth, int columnCount);
	void Render(const RenderParams &params);
	void Loop(int frame);
	void MoveTo(e::XMVECTOR pos);
};