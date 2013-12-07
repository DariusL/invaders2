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
#include "MirrorShader.h"
#include "InstancedTextureShader.h"
#include "ShadowShader.h"

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
	vector<TexturedModel> texturedModels;
	vector<shared_ptr<Level>> levels;
	vector<unique_ptr<IShader>> shaders;
	ComVector<ID3D11ShaderResourceView> textures;

	static NormalModel GetNormalModelFromOBJ(wstring filename, bool invert = false);
	static ColorModel GetModelFromOBJ(wstring filename, bool invert = false);
	static NormalMappedModel GetNormalMappedModelFromOBJ(wstring filename, bool invert = false);
	static TexturedModel GetTexturedModelFromOBJ(wstring filename, bool invert = false);
	static TexturedModel GetTexturedModelFromOBJUnindexed(wstring filename, bool invert = false);
	static void CalculateTangentAndBinormal(const vector<FaceVertex> &ind, vector<NormalMappedVertexType> &v);
	static vector<FaceVertex> GetVerticesFromFace(string &line);
	static FaceVertex GetVertexFromString(string &vertex);
	static ComPtr<ID3D11ShaderResourceView> GetTextureFromFile(wstring filename, ComPtr<ID3D11Device> device);

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager &operator=(const ResourceManager&) = delete;
	static ResourceManager *handle;
public:
	ResourceManager(void);
	~ResourceManager(void);

	void Init();
	void InitShaders(Microsoft::WRL::ComPtr<ID3D11Device>);
	ColorModel &GetModel(int i){return models[i];}
	shared_ptr<DrawableShooter> GetEnemy(int type);
	shared_ptr<Level> GetLevel(int type){return levels[type];}
	TexturedModel &GetTexturedModel(int i){ return texturedModels[i]; }
	ComPtr < ID3D11ShaderResourceView> GetTexture(int i){ return textures[i]; }
	static ResourceManager &Get(){ return *handle; }

	template<class sh>
	sh &GetShader(){}
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
	template<>
	MirrorShader &GetShader<MirrorShader>(){ return static_cast<MirrorShader&>(*shaders[Shaders::MIRROR]); }
	template<>
	InstancedTextureShader &GetShader<InstancedTextureShader>(){ return static_cast<InstancedTextureShader&>(*shaders[Shaders::TEXTURE_INSTANCED]); }
	template<>
	ShadowShader &GetShader<ShadowShader>(){ return static_cast<ShadowShader&>(*shaders[Shaders::SHADOW]); }

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
		WATER,
		MIRROR,
		TEXTURE_INSTANCED,
		SHADOW
	};

	enum Textures
	{
		TEXTURE_GABEN,
		TEXTURE_WATER_NORMAL_MAP,
		WALL,
		TREE
	};

	enum TexturedModels
	{
		PLANE,
		INV_BOX,
		BATH
	};
};

typedef ResourceManager RM;