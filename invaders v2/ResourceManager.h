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
#include "CelComputeShader.h"
#include "DownSampleComputeShader.h"
#include "UpSampleComputeShader.h"
#include "HorizontalBlurComputeShader.h"
#include "VerticalBlurComputeShader.h"

using namespace std;

class ResourceManager
{
public:
	enum MODEL
	{
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
		SHADER_SHADOW
	};

	enum SHADER_COMPUTE
	{
		SHADER_COMPUTE_CEL,
		SHADER_COMPUTE_UPSAMPLE,
		SHADER_COMPUTE_DOWNSAMPLE,
		SHADER_COMPUTE_HORIZONTAL_BLUR,
		SHADER_COMPUTE_VERTICAL_BLUR
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
		TEXTURED_MODEL_BATH
	};

	enum NORMAL_TEXTURED_MODEL
	{
		NORMAL_TEXTURED_MODEL_INV_BOX,
		NORMAL_TEXTURED_MODEL_PLANE,
		NORMAL_TEXTURED_MODEL_BATH
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

	static NormalModel GetNormalModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool invert = false);
	static ColorModel GetModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool invert = false);
	static NormalMappedModel GetNormalMappedModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool invert = false);
	static TexturedModel GetTexturedModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool unindex = false, bool invert = false);
	static NormalTexturedModel GetNormalTexturedModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool unindex = false, bool invert = false);

	static void CalculateTangentAndBinormal(const vector<FaceVertex> &ind, vector<NormalMappedVertexType> &v);
	static vector<FaceVertex> GetVerticesFromFace(string &line);
	static FaceVertex GetVertexFromString(string &vertex);
	static ComPtr<ID3D11ShaderResourceView> GetTextureFromFile(wstring filename, ComPtr<ID3D11Device> device);

	static ResourceManager *handle;
public:
	ResourceManager(Microsoft::WRL::ComPtr<ID3D11Device> device);
	~ResourceManager(void){}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager &operator=(const ResourceManager&) = delete;

	ColorModel &GetModel(MODEL i){ return models[i]; }
	NormalTexturedModel &GetNormalTexturedModel(NORMAL_TEXTURED_MODEL i){ return normalTexturedModels[i]; }
	TexturedModel &GetTexturedModel(TEXTURED_MODEL i){ return texturedModels[i]; }
	NormalMappedModel &GetNormalMappedModel(){ return normalMappedModel; }
	ComPtr < ID3D11ShaderResourceView> GetTexture(TEXTURE i){ return textures[i]; }

	shared_ptr<Level> GetLevel(int type){ return levels[type]; }
	static ResourceManager &Get(){ return *handle; }

	//because why not
	template<class sh>
	sh &GetShader(){}
	template<>
	ColorShader &GetShader<ColorShader>(){ return static_cast<ColorShader&>(*shaders[SHADER::SHADER_COLOR]); }
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
	CelComputeShader &GetShader<CelComputeShader>(){ return static_cast<CelComputeShader&>(*computeShaders[SHADER_COMPUTE::SHADER_COMPUTE_CEL]); }
	template<>
	DownSampleComputeShader &GetShader<DownSampleComputeShader>(){ return static_cast<DownSampleComputeShader&>(*computeShaders[SHADER_COMPUTE::SHADER_COMPUTE_DOWNSAMPLE]); }
	template<>
	UpSampleComputeShader &GetShader<UpSampleComputeShader>(){ return static_cast<UpSampleComputeShader&>(*computeShaders[SHADER_COMPUTE::SHADER_COMPUTE_UPSAMPLE]); }
	template<>
	HorizontalBlurComputeShader &GetShader<HorizontalBlurComputeShader>(){ return static_cast<HorizontalBlurComputeShader&>(*computeShaders[SHADER_COMPUTE::SHADER_COMPUTE_HORIZONTAL_BLUR]); }
	template<>
	VerticalBlurComputeShader &GetShader<VerticalBlurComputeShader>(){ return static_cast<VerticalBlurComputeShader&>(*computeShaders[SHADER_COMPUTE::SHADER_COMPUTE_VERTICAL_BLUR]); }
};

typedef ResourceManager RM;