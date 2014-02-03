#pragma once

#include "includes.h"
#include "Model.h"
#include "DrawableShooter.h"
#include "Level.h"
#include "ColorInstancedShader.h"
#include "ColorShader.h"
#include "GlobalDiffuseShader.h"
#include "GlobalSpecularShader.h"
#include "TextureShader.h"
#include "InstancedTextureShader.h"
#include "CelComputeShader.h"
#include "DownSampleComputeShader.h"
#include "UpSampleComputeShader.h"
#include "HorizontalBlurComputeShader.h"
#include "VerticalBlurComputeShader.h"
#include "FilterDownSampleShader.h"
#include "TexelSumComputeShader.h"

using namespace std;

class ResourceManager
{
public:
	enum MODEL
	{
		MODEL_BALL,
		MODEL_PLANE,
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
		SHADER_TEXTURE,
		SHADER_TEXTURE_INSTANCED,
	};

	enum SHADER_COMPUTE
	{
		SHADER_COMPUTE_CEL,
		SHADER_COMPUTE_UPSAMPLE,
		SHADER_COMPUTE_DOWNSAMPLE,
		SHADER_COMPUTE_HORIZONTAL_BLUR,
		SHADER_COMPUTE_VERTICAL_BLUR,
		SHADER_COMPUTE_FILTER_DOWNSAMPLE,
		SHADER_COMPUTE_TEXEL_SUM
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
	vector<shared_ptr<Level>> levels;
	vector<unique_ptr<ComputeShader>> computeShaders;
	vector<unique_ptr<IShader>> shaders;
	ComVector<ID3D11ShaderResourceView> textures;
	unordered_map<char, Geometry<VertexType>> letters;

	static Geometry<NormalVertexType> GetNormalModelFromOBJ(wstring filename, bool invert = false);
	static Geometry<VertexType> GetModelFromOBJ(wstring filename, bool invert = false);
	static unordered_map<char, Geometry<VertexType>> GetModelsFromOBJ(wstring filename);

	static vector<FaceVertex> GetVerticesFromFace(string &line, int voff = 1, int noff = 1, int toff = 1);
	static FaceVertex GetVertexFromString(string &vertex, int voff = 1, int noff = 1, int toff = 1);
	static ComPtr<ID3D11ShaderResourceView> GetTextureFromFile(wstring filename, ID3D11Device *device);

	static ResourceManager *handle;
public:
	ResourceManager(ID3D11Device *device);
	~ResourceManager(void){}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager &operator=(const ResourceManager&) = delete;

	ColorModel &GetModel(MODEL i){ return models[i]; }
	ID3D11ShaderResourceView *GetTexture(TEXTURE i){ return textures[i].Get(); }
	const Geometry<VertexType> &GetLetter(char letter){ return letters[letter]; }

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
	TextureShader &GetShader<TextureShader>(){ return static_cast<TextureShader&>(*shaders[SHADER::SHADER_TEXTURE]); }
	template<>
	InstancedTextureShader &GetShader<InstancedTextureShader>(){ return static_cast<InstancedTextureShader&>(*shaders[SHADER::SHADER_TEXTURE_INSTANCED]); }

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
	template<>
	FilterDownSampleShader &GetShader<FilterDownSampleShader>(){ return static_cast<FilterDownSampleShader&>(*computeShaders[SHADER_COMPUTE::SHADER_COMPUTE_FILTER_DOWNSAMPLE]); }
	template<>
	TexelSumComputeShader &GetShader<TexelSumComputeShader>(){ return static_cast<TexelSumComputeShader&>(*computeShaders[SHADER_COMPUTE::SHADER_COMPUTE_TEXEL_SUM]); }
};

typedef ResourceManager RM;