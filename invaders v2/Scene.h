#pragma once
#pragma warning(disable : 4005)
#include "iworld.h"
#include "DrawableShooter.h"
#include "DrawableTexturedEntity.h"
#include "Globals.h"
#include "Light.h"
#include "FloatingCamera.h"
#include "DrawableBumpyEntity.h"
#include "WaterPlane.h"
#include "RemoteCamera.h"
class Scene : public IWorld
{
	shared_ptr<DrawableBumpyEntity> bumpy;
	shared_ptr<Light> light;
	RemoteCamera remoteCamera;
	SimpleTexturedEntity gabenizer;
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	shared_ptr<Light> GetLight(){return light;}
	RemoteCamera &GetRemoteCamera(){ return remoteCamera; }
	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
};