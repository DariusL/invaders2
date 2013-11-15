#pragma once
#include "iworld.h"
#include "DrawableShooter.h"
#include "DrawableTexturedEntity.h"
#include "Globals.h"
#include "Light.h"
#include "DrawableBumpyEntity.h"
#include "WaterPlane.h"
#include "RemoteCamera.h"
#include "Mirror.h"
#include "WaterPlane.h"
class Scene : public IWorld
{
	DrawableBumpyEntity bumpy;
	Light light;
	vector<RemoteCamera> cameras;
	vector<SimpleMirror> mirrors;
	SimpleTexturedEntity gabenizer;
	SimpleWaterPlane water;
	SimpleTexturedEntity bath;
	DrawableEntity<NormalVertexType, PointSpecularShader> thing;
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	Light &GetLight(){ return light; }
	vector<SimpleMirror> &GetMirrors(){ return mirrors; }
	vector<RemoteCamera> &GetRemoteCameras(){ return cameras; }
	SimpleWaterPlane &GetWater(){ return water; }
	void Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
};