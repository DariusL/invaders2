#pragma once

#include "includes.h"
#include "Models.h"
#include "DrawableShooter.h"
#include "Level.h"

using namespace std;

class ResourceManager
{
	vector<shared_ptr<ColorModel>> models;
	shared_ptr<Model<NormalVertexType>> normalModel;
	shared_ptr<NormalMappedModel> texturedModel;
	shared_ptr<TexturedModel> plane;
	vector<shared_ptr<Level>> levels;
	vector<shared_ptr<IShader>> shaders;

	unique_ptr<NormalModel> GetNormalModelFromOBJ(char *filename);
	unique_ptr<ColorModel> GetModelFromOBJ(char *filename);
	unique_ptr<NormalMappedModel> GetTexturedModelFromOBJ(char *filename);
	void CalculateTangentAndBinormal(const vector<int> &ind, vector<NormalMappedVertexType> &v);
public:
	ResourceManager(void);
	~ResourceManager(void);

	bool Init();
	shared_ptr<ColorModel> GetModel(int i){return models[i];}
	shared_ptr<DrawableShooter> GetEnemy(int type);
	shared_ptr<Level> GetLevel(int type){return levels[type];}
	shared_ptr<NormalModel> GetNormalModel(){return normalModel;}
	shared_ptr<TexturedModel> GetPlane(){return plane;}
	shared_ptr<NormalMappedModel> GetTexturedModel(){return texturedModel;}

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
		TEXTURE,
		NORMAL_MAPPED,
		WATER
	};

	enum NormalModels
	{
		NORMAL_TEACUP
	};
};