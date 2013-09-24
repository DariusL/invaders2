#pragma once
#pragma warning(disable : 4005)
#include "iworld.h"
#include "DrawableShooter.h"
#include "DrawableEntity.h"
#include "Globals.h"
#include "Light.h"
#include "FloatingCamera.h"
class Scene : public IWorld
{
	vector<shared_ptr<DrawableEntity>> random;
	vector<shared_ptr<FloatingCamera>> cameras;
	shared_ptr<Light> light;
	float yaw;
	float pitch;
	float r;
	float lightPitch;
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	shared_ptr<Light> GetLight(){return light;}
	const vector<shared_ptr<FloatingCamera>> GetCameras(){return cameras;}
	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
};

