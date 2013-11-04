#pragma once

#include "includes.h"
#include "Models.h"
#include "DrawableShooter.h"
#include "Level.h"
#include "ColorInstancedShader.h"
#include "ColorShader.h"
#include "GlobalDiffuseShader.h"
#include "GlobalSpecularShader.h"
#include "PointDiffuseShader.h"
#include "PointSpecularShader.h"
#include "TextureShader.h"
#include "NormalMappedShader.h"
#include "WaterShader.h"

using namespace std;

class ResourceManager
{
	struct FaceVertex
	{
		int normal;
		int tex;
		int vertex;
	};
	vector<shared_ptr<ColorModel>> models;
	shared_ptr<Model<NormalVertexType>> normalModel;
	shared_ptr<NormalMappedModel> texturedModel;
	shared_ptr<TexturedModel> plane;
	vector<shared_ptr<Level>> levels;
	vector<shared_ptr<IShader>> shaders;

	unique_ptr<NormalModel> GetNormalModelFromOBJ(char *filename);
	unique_ptr<ColorModel> GetModelFromOBJ(char *filename);
	unique_ptr<NormalMappedModel> GetTexturedModelFromOBJ(char *filename);
	void CalculateTangentAndBinormal(const vector<FaceVertex> &ind, vector<NormalMappedVertexType> &v);
	vector<FaceVertex> GetVerticesFromFace(string &line);
	FaceVertex GetVertexFromString(string &vertex);
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

	template<class sh>
	shared_ptr<sh> GetShader(){return nullptr;}
	template<>
	shared_ptr<ColorShader> GetShader<ColorShader>(){return static_pointer_cast<ColorShader, IShader>(shaders[Shaders::COLOR]);}
	template<>
	shared_ptr<ColorInstancedShader> GetShader<ColorInstancedShader>(){return static_pointer_cast<ColorInstancedShader, IShader>(shaders[Shaders::COLOR_INSTANCED]);}
	template<>
	shared_ptr<TextureShader> GetShader<TextureShader>(){return static_pointer_cast<TextureShader, IShader>(shaders[Shaders::TEXTURE]);}
	template<>
	shared_ptr<GlobalDiffuseShader> GetShader<GlobalDiffuseShader>(){return static_pointer_cast<GlobalDiffuseShader, IShader>(shaders[Shaders::GLOBAL_DIFFUSE]);}
	template<>
	shared_ptr<GlobalSpecularShader> GetShader<GlobalSpecularShader>(){return static_pointer_cast<GlobalSpecularShader, IShader>(shaders[Shaders::GLOBAL_SPECULAR]);}
	template<>
	shared_ptr<PointDiffuseShader> GetShader<PointDiffuseShader>(){return static_pointer_cast<PointDiffuseShader, IShader>(shaders[Shaders::POINT_DIFFUSE]);}
	template<>
	shared_ptr<PointSpecularShader> GetShader<PointSpecularShader>(){return static_pointer_cast<PointSpecularShader, IShader>(shaders[Shaders::POINT_SPECULAR]);}
	template<>
	shared_ptr<WaterShader> GetShader<WaterShader>(){return static_pointer_cast<WaterShader, IShader>(shaders[Shaders::WATER]);}
	template<>
	shared_ptr<NormalMappedShader> GetShader<NormalMappedShader>(){return static_pointer_cast<NormalMappedShader, IShader>(shaders[Shaders::NORMAL_MAPPED]);}

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