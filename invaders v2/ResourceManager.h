#pragma once

#include <vector>
#include <memory>
#include <wrl\client.h>

#include "Model.h"
#include "ColorInstancedShader.h"
#include "ColorShader.h"
#include "Shooter.h"
#include "Level.h"

using namespace std;

class ResourceManager
{
	vector<shared_ptr<Model>> models;
	vector<D3DXVECTOR2> hitboxes;
	vector<shared_ptr<Level>> levels;

	shared_ptr<ColorShader> colorShader;
	shared_ptr<ColorInstancedShader> colorInstancedShader;
public:
	ResourceManager(void);
	~ResourceManager(void);

	bool Init();
	shared_ptr<Model> GetModel(int i){return models[i];}
	const D3DXVECTOR2 &GetHitbox(int i){return hitboxes[i];}
	shared_ptr<Shooter> GetEnemy(int type);
	shared_ptr<Level> GetLevel(int type){return levels[type];}

	shared_ptr<ColorShader> GetColorShader(){return colorShader;}
	shared_ptr<ColorInstancedShader> GetColorInstancedShader(){return colorInstancedShader;}

	bool InitShaders(Microsoft::WRL::ComPtr<ID3D11Device>);

	enum Models
	{
		MODEL_PLAYER = 0,
		MODEL_ENEMY_BASIC,
		MODEL_BULLET,
		MODEL_ENEMY_LAPTOP
	};

	enum Hitboxes
	{
		HITBOX_PLAYER = 0,
		HITBOX_ENEMY,
		HITBOX_BULLET,
		HITBOX_ENEMY_GAP
	};

	enum Enemies
	{
		BASIC = 0,
		LAPTOP
	};

	enum Levels
	{
		L1 = 0
	};
};