#pragma once

#include "includes.h"
#include "Model.h"
#include "Level.h"
#include "ColorInstancedShader.h"
#include "ColorShader.h"
#include "GlobalDiffuseShader.h"

using namespace std;

class ResourceManager
{
	struct FaceVertex
	{
		int normal;
		int tex;
		int vertex;
	};
	NormalModel normalModel;
	vector<unique_ptr<IShader>> shaders;

	static NormalModel GetNormalModelFromOBJ(string filename, bool invert = false);
	static ColorModel GetModelFromOBJ(string filename, bool invert = false);
	static vector<FaceVertex> GetVerticesFromFace(string &line);
	static FaceVertex GetVertexFromString(string &vertex);

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager &operator=(const ResourceManager&) = delete;
	static ResourceManager *handle;
public:
	ResourceManager(void);
	~ResourceManager(void);

	void Init();
	void InitShaders(Microsoft::WRL::ComPtr<ID3D11Device>);
	NormalModel &GetNormalModel(){return normalModel;}
	static ResourceManager &Get(){ return *handle; }

	template<class sh>
	sh &GetShader(){}
	template<>
	ColorShader &GetShader<ColorShader>(){return static_cast<ColorShader&>(*shaders[Shaders::COLOR]);}
	template<>
	ColorInstancedShader &GetShader<ColorInstancedShader>(){return static_cast<ColorInstancedShader&>(*shaders[Shaders::COLOR_INSTANCED]);}
	template<>
	GlobalDiffuseShader &GetShader<GlobalDiffuseShader>(){return static_cast<GlobalDiffuseShader&>(*shaders[Shaders::GLOBAL_DIFFUSE]);}

	enum Shaders
	{
		COLOR,
		COLOR_INSTANCED,
		GLOBAL_DIFFUSE
	};

	enum NormalModels
	{
		NORMAL_TEACUP,
		NORMAL_THING
	};
};

typedef ResourceManager RM;