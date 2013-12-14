#pragma once
#include "iworld.h"
#include "DrawableShooter.h"
#include "DrawableTexturedEntity.h"
#include "Globals.h"
#include "ShadowLight.h"
#include "DrawableBumpyEntity.h"
#include "WaterPlane.h"
#include "RemoteCamera.h"
#include "Mirror.h"
#include "WaterPlane.h"
#include "Billboard.h"
#include "ShadowShader.h"
#include "MirrorBall.h"

class Scene : public IWorld
{
	ShadowLight light;
	vector<RemoteCamera> cameras;
	vector<SimpleMirror> mirrors;
	DrawableTexturedEntity<NormalTextureVertexType, ShadowShader> gabenizer;
	SimpleWaterPlane water;
	DrawableTexturedEntity<NormalTextureVertexType, ShadowShader> bath;
	Billboard<TextureVertexType, TextureShader> billboard;
	DrawableTexturedEntity<NormalTextureVertexType, ShadowShader> ground;
	DrawableTexturedEntity<NormalTextureVertexType, ShadowShader> wall;
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	ShadowLight &GetLight(){ return light; }
	vector<SimpleMirror> &GetMirrors(){ return mirrors; }
	vector<RemoteCamera> &GetRemoteCameras(){ return cameras; }
	SimpleWaterPlane &GetWater(){ return water; }
	void Init(ComPtr<ID3D11Device> device);
	void Render(RenderParams &params);
	void GetRenderBalls(vector<MirrorBall*> &mirrors);
};