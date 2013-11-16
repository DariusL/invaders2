#pragma once

#include "includes.h"
#include "Model.h"
#include "Level.h"
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
	GlobalDiffuseShader shader;

	static NormalModel GetNormalModelFromOBJ(string filename, bool invert = false);
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

	GlobalDiffuseShader &GetShader(){ return shader; }

	enum NormalModels
	{
		NORMAL_TEACUP,
		NORMAL_THING
	};
};

typedef ResourceManager RM;