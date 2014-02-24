#pragma once
#include "includes.h"
#include "IDrawable.h"
#include "EnemyList.h"
#include "Entity.h"
#include "ResourceManager.h"

class Grid : public IDrawable, public Entity
{
	e::unordered_map<int, e::unique_ptr<EnemyList>> instancers;
public:
	Grid(ID3D11Device *device, e::XMVECTOR pos, e::XMFLOAT2 size, const RM::Level &level);
	void Render(const RenderParams &params);
};