#pragma once

#include "includes.h"
#include "NormalModel.h"
#include "TexturedNormalModel.h"
#include "Model.h"
#include "DrawableShooter.h"
#include "Level.h"

using namespace std;

class ResourceManager
{
	vector<shared_ptr<Model>> models;
	shared_ptr<NormalModel> normalModel;
	shared_ptr<TexturedNormalModel> texturedModel;
	vector<shared_ptr<Level>> levels;
	vector<shared_ptr<IShader>> shaders;

	unique_ptr<NormalModel> GetNormalModelFromOBJ(char *filename);
	unique_ptr<Model> GetModelFromOBJ(char *filename);
	unique_ptr<TexturedNormalModel> GetTexturedModelFromOBJ(char *filename);
	void CalculateTangentAndBinormal(const vector<int> &ind, vector<TextureVertexType> &v);
public:
	ResourceManager(void);
	~ResourceManager(void);

	bool Init();
	shared_ptr<Model> GetModel(int i){return models[i];}
	shared_ptr<DrawableShooter> GetEnemy(int type);
	shared_ptr<Level> GetLevel(int type){return levels[type];}
	shared_ptr<NormalModel> GetNormalModel(){return normalModel;}
	shared_ptr<TexturedNormalModel> GetTexturedModel(){return texturedModel;}

	shared_ptr<IShader> GetShader(int shader){return shaders[shader];}

	bool InitShaders(Microsoft::WRL::ComPtr<ID3D11Device>);

	enum Models
	{
		MODEL_PLAYER = 0,
		MODEL_ENEMY_BASIC,
		MODEL_BULLET,
		MODEL_ENEMY_LAPTOP,
		MODEL_WALL,
		MODEL_BALL
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
		GLOBAL_DIFFUSE,
		GLOBAL_SPECULAR,
		POINT_DIFFUSE,
		POINT_SPECULAR,
		TEXTURE
	};

	enum NormalModels
	{
		NORMAL_TEACUP
	};
};