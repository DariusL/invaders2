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
#include "HorizontalBlurShader.h"
#include "VerticalBlurShader.h"
#include "CelComputeShader.h"

using namespace std;

class ResourceManager
{
public:
	enum MODEL
	{
		MODEL_PLAYER = 0,
		MODEL_ENEMY_BASIC,
		MODEL_BULLET,
		MODEL_ENEMY_LAPTOP,
		MODEL_WALL,
		MODEL_BALL
	};

	enum ENEMY
	{
		ENEMY_BASIC = 0,
		ENEMY_LAPTOP
	};

	enum LEVEL
	{
		L1 = 0
	};

	enum SHADER
	{
		SHADER_COLOR,
		SHADER_COLOR_INSTANCED,
		SHADER_GLOBAL_DIFFUSE,
		SHADER_GLOBAL_SPECULAR,
		SHADER_POINT_DIFFUSE,
		SHADER_POINT_SPECULAR,
		SHADER_TEXTURE,
		SHADER_NORMAL_MAPPED,
		SHADER_WATER,
		SHADER_MIRROR,
		SHADER_TEXTURE_INSTANCED,
		SHADER_SHADOW,
		SHADER_HORIZONTAL_BLUR,
		SHADER_VERTICAL_BLUR,
	};

	enum SHADER_COMPUTE
	{
		SHADER_COMPUTE_CEL
	};

	enum TEXTURE
	{
		TEXTURE_GABEN,
		TEXTURE_WATER_NORMAL_MAP,
		TEXTURE_WALL,
		TEXTURE_TREE
	};

	enum TEXTURED_MODEL
	{
		TEXTURED_MODEL_PLANE,
		TEXTURED_MODEL_INV_BOX,
		TEXTURED_MODEL_BATH,
		TEXTURED_MODEL_HARBINGER
	};

	enum NORMAL_TEXTURED_MODEL
	{
		NORMAL_TEXTURED_MODEL_INV_BOX,
		NORMAL_TEXTURED_PLANE,
		NORMAL_TEXTURED_BATH
	};

private:
	struct FaceVertex
	{
		int normal;
		int tex;
		int vertex;
	};
	vector<ColorModel> models;
	vector<TexturedModel> texturedModels;
	vector<NormalTexturedModel> normalTexturedModels;
	vector<shared_ptr<Level>> levels;
	vector<unique_ptr<ComputeShader>> computeShaders;
	vector<unique_ptr<IShader>> shaders;
	ComVector<ID3D11ShaderResourceView> textures;
	NormalMappedModel normalMappedModel;

	static NormalModel GetNormalModelFromOBJ(wstring filename, bool invert = false);
	static ColorModel GetModelFromOBJ(wstring filename, bool invert = false);
	static NormalMappedModel GetNormalMappedModelFromOBJ(wstring filename, bool invert = false);
	static TexturedModel GetTexturedModelFromOBJ(wstring filename, bool invert = false);
	static TexturedModel GetTexturedModelFromOBJUnindexed(wstring filename, bool invert = false);
	static NormalTexturedModel GetNormalTexturedModelFromOBJUnindexed(wstring filename, bool invert = false);
	static void CalculateTangentAndBinormal(const vector<FaceVertex> &ind, vector<NormalMappedVertexType> &v);
	static vector<FaceVertex> GetVerticesFromFace(string &line);
	static FaceVertex GetVertexFromString(string &vertex);
	static ComPtr<ID3D11ShaderResourceView> GetTextureFromFile(wstring filename, ComPtr<ID3D11Device> device);

	
	static ResourceManager *handle;
public:
	ResourceManager(Microsoft::WRL::ComPtr<ID3D11Device> device);
	~ResourceManager(void);

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager &operator=(const ResourceManager&) = delete;

	ColorModel &GetModel(MODEL i){return models[i];}
	NormalTexturedModel &GetNormalTexturedModel(NORMAL_TEXTURED_MODEL i){ return normalTexturedModels[i]; }
	TexturedModel &GetTexturedModel(TEXTURED_MODEL i){ return texturedModels[i]; }
	NormalMappedModel &GetNormalMappedModel(){ return normalMappedModel; }
	ComPtr < ID3D11ShaderResourceView> GetTexture(TEXTURE i){ return textures[i]; }

	shared_ptr<DrawableShooter> GetEnemy(int type);
	shared_ptr<Level> GetLevel(int type){return levels[type];}
	static ResourceManager &Get(){ return *handle; }

	template<class sh>
	sh &GetShader(){}
	template<>
	ColorShader &GetShader<ColorShader>(){return static_cast<ColorShader&>(*shaders[SHADER::SHADER_COLOR]);}
	template<>
	ColorInstancedShader &GetShader<ColorInstancedShader>(){ return static_cast<ColorInstancedShader&>(*shaders[SHADER::SHADER_COLOR_INSTANCED]); }
	template<>
	GlobalDiffuseShader &GetShader<GlobalDiffuseShader>(){ return static_cast<GlobalDiffuseShader&>(*shaders[SHADER::SHADER_GLOBAL_DIFFUSE]); }
	template<>
	GlobalSpecularShader &GetShader<GlobalSpecularShader>(){ return static_cast<GlobalSpecularShader&>(*shaders[SHADER::SHADER_GLOBAL_SPECULAR]); }
	template<>
	PointDiffuseShader &GetShader<PointDiffuseShader>(){ return static_cast<PointDiffuseShader&>(*shaders[SHADER::SHADER_POINT_DIFFUSE]); }
	template<>
	PointSpecularShader &GetShader<PointSpecularShader>(){ return static_cast<PointSpecularShader&>(*shaders[SHADER::SHADER_POINT_SPECULAR]); }
	template<>
	TextureShader &GetShader<TextureShader>(){ return static_cast<TextureShader&>(*shaders[SHADER::SHADER_TEXTURE]); }
	template<>
	NormalMappedShader &GetShader<NormalMappedShader>(){ return static_cast<NormalMappedShader&>(*shaders[SHADER::SHADER_NORMAL_MAPPED]); }
	template<>
	WaterShader &GetShader<WaterShader>(){ return static_cast<WaterShader&>(*shaders[SHADER::SHADER_WATER]); }
	template<>
	MirrorShader &GetShader<MirrorShader>(){ return static_cast<MirrorShader&>(*shaders[SHADER::SHADER_MIRROR]); }
	template<>
	InstancedTextureShader &GetShader<InstancedTextureShader>(){ return static_cast<InstancedTextureShader&>(*shaders[SHADER::SHADER_TEXTURE_INSTANCED]); }
	template<>
	ShadowShader &GetShader<ShadowShader>(){ return static_cast<ShadowShader&>(*shaders[SHADER::SHADER_SHADOW]); }
	template<>
	HorizontalBlurShader &GetShader<HorizontalBlurShader>(){ return static_cast<HorizontalBlurShader&>(*shaders[SHADER::SHADER_HORIZONTAL_BLUR]); }
	template<>
	VerticalBlurShader &GetShader<VerticalBlurShader>(){ return static_cast<VerticalBlurShader&>(*shaders[SHADER::SHADER_VERTICAL_BLUR]); }
	template<>
	CelComputeShader &GetShader<CelComputeShader>(){ return static_cast<CelComputeShader&>(*computeShaders[SHADER_COMPUTE::SHADER_COMPUTE_CEL]); }
};

typedef ResourceManager RM;