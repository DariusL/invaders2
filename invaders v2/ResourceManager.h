#pragma once

#include "includes.h"
#include "Model.h"
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
	vector<ColorModel> models;
	NormalModel normalModel;
	NormalMappedModel texturedModel;
	TexturedModel plane;
	vector<shared_ptr<Level>> levels;
	vector<shared_ptr<IShader>> shaders;

	static NormalModel GetNormalModelFromOBJ(string filename);
	static ColorModel GetModelFromOBJ(string filename);
	static NormalMappedModel GetTexturedModelFromOBJ(string filename);
	static void CalculateTangentAndBinormal(const vector<FaceVertex> &ind, vector<NormalMappedVertexType> &v);
	static vector<FaceVertex> GetVerticesFromFace(string &line);
	static FaceVertex GetVertexFromString(string &vertex);

	ResourceManager(const ResourceManager&);
	ResourceManager &operator=(const ResourceManager&);
public:
	ResourceManager(void);
	~ResourceManager(void);

	ResourceManager(ResourceManager&&){}
	ResourceManager &operator=(ResourceManager&&){}

	bool Init();
	ColorModel &GetModel(int i){return models[i];}
	shared_ptr<DrawableShooter> GetEnemy(int type);
	shared_ptr<Level> GetLevel(int type){return levels[type];}
	NormalModel &GetNormalModel(){return normalModel;}
	TexturedModel &GetPlane(){return plane;}
	NormalMappedModel &GetTexturedModel(){return texturedModel;}

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