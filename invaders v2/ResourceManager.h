#pragma once
#include "Model.h"
#include <vector>
#include <memory>
using namespace std;
class ResourceManager
{
	vector<Model*> models;
	vector<D3DXVECTOR2> hitboxes;
public:
	ResourceManager(void);
	~ResourceManager(void);

	bool Init();
	Model *GetModel(int i){return models[i];}
	const D3DXVECTOR2 &GetHitbox(int i){return hitboxes[i];}

	enum ModelCodes{
		MODEL_PLAYER = 0,
		MODEL_ENEMY,
		MODEL_BULLET
	};

	enum Hitboxes{
		HITBOX_PLAYER = 0,
		HITBOX_ENEMY,
		HITBOX_BULLET,
		HITBOX_ENEMY_GAP
	};
};

