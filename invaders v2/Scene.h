#pragma once
#pragma warning(disable : 4005)
#include "iworld.h"
#include "DrawableShooter.h"
#include "DrawableTexturedEntity.h"
#include "Globals.h"
#include "Light.h"
#include "DrawableBumpyEntity.h"
#include "WaterPlane.h"
#include "RemoteCamera.h"
#include "Mirror.h"
class Scene : public IWorld
{
	DrawableBumpyEntity bumpy;
	Light light;
	vector<RemoteCamera> cameras;
	SimpleTexturedEntity gabenizer;
	SimpleMirror mirror;
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	Light &GetLight(){ return light; }
	SimpleMirror &GetMirror(){ return mirror; }
	vector<RemoteCamera> &GetRemoteCamera(){ return cameras; }
	void Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
};