#pragma once
#include "Model.h"
#include <vector>
#include <memory>
using namespace std;
class ResourceManager
{
	vector<Model*> models;
	int modelCount;
public:
	ResourceManager(void);
	~ResourceManager(void);

	bool Init();
	Model *GetModel(int i){return models[i];}

	enum ModelCodes{
		PLAYER = 0,
		ENEMY,
		BULLET
	};
};

