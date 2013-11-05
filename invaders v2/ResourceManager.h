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
	vector<unique_ptr<IShader>> shaders;

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
	sh &GetShader(){return ColorShader("", "");}
	template<>
	ColorShader &GetShader<ColorShader>(){return static_cast<ColorShader&>(*shaders[Shaders::COLOR]);}
	template<>
	ColorInstancedShader &GetShader<ColorInstancedShader>(){return static_cast<ColorInstancedShader&>(*shaders[Shaders::COLOR_INSTANCED]);}
	template<>
	GlobalDiffuseShader &GetShader<GlobalDiffuseShader>(){return static_cast<GlobalDiffuseShader&>(*shaders[Shaders::GLOBAL_DIFFUSE]);}
	template<>
	GlobalSpecularShader &GetShader<GlobalSpecularShader>(){return static_cast<GlobalSpecularShader&>(*shaders[Shaders::GLOBAL_SPECULAR]);}
	template<>
	PointDiffuseShader &GetShader<PointDiffuseShader>(){return static_cast<PointDiffuseShader&>(*shaders[Shaders::POINT_DIFFUSE]);}
	template<>
	PointSpecularShader &GetShader<PointSpecularShader>(){return static_cast<PointSpecularShader&>(*shaders[Shaders::POINT_SPECULAR]);}
	template<>
	TextureShader &GetShader<TextureShader>(){return static_cast<TextureShader&>(*shaders[Shaders::TEXTURE]);}
	template<>
	NormalMappedShader &GetShader<NormalMappedShader>(){return static_cast<NormalMappedShader&>(*shaders[Shaders::NORMAL_MAPPED]);}
	template<>
	WaterShader &GetShader<WaterShader>(){return static_cast<WaterShader&>(*shaders[Shaders::WATER]);}

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