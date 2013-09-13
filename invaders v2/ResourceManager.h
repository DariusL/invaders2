#pragma once

#include <vector>
#include <memory>
#include <wrl\client.h>

#include "NormalModel.h"
#include "Model.h"
#include "ColorInstancedShader.h"
#include "GlobalDiffuseShader.h"
#include "ColorShader.h"
#include "DrawableShooter.h"
#include "Level.h"

using namespace std;

class ResourceManager
{
	vector<shared_ptr<Model>> models;
	shared_ptr<NormalModel> normalModel;
	vector<shared_ptr<Level>> levels;

	shared_ptr<ColorShader> colorShader;
	shared_ptr<ColorInstancedShader> colorInstancedShader;
	vector<shared_ptr<IShader>> shaders;

	unique_ptr<NormalModel> GetModelFromOBJ(char *filename);
public:
	ResourceManager(void);
	~ResourceManager(void);

	bool Init();
	shared_ptr<Model> GetModel(int i){return models[i];}
	shared_ptr<DrawableShooter> GetEnemy(int type);
	shared_ptr<Level> GetLevel(int type){return levels[type];}
	shared_ptr<NormalModel> GetNormalModel(){return normalModel;}

	shared_ptr<IShader> GetShader(int shader){return shaders[shader];}

	bool InitShaders(Microsoft::WRL::ComPtr<ID3D11Device>);

	enum Models
	{
		MODEL_PLAYER = 0,
		MODEL_ENEMY_BASIC,
		MODEL_BULLET,
		MODEL_ENEMY_LAPTOP,
		MODEL_WALL
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

	enum Shaders
	{
		COLOR,
		COLOR_INSTANCED,
		GLOBAL_DIFFUSE
	};

	enum NormalModels
	{
		NORMAL_TEACUP
	};
};