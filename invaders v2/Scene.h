#pragma once
#pragma warning(disable : 4005)
#include "iworld.h"
#include "DrawableShooter.h"
#include "DrawableEntity.h"
#include "Globals.h"
#include "Light.h"
class Scene : public IWorld
{
	vector<shared_ptr<DrawableEntity>> random;
	shared_ptr<Light> light;
	float yaw;
	float pitch;
	float r;
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	shared_ptr<Light> GetLight(){return light;}

	bool Init(ComPtr<ID3D11Device>);
	void Render(RenderParams);
};

