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
#include "Particles.h"

class Scene : public IWorld
{
	ShadowLight light;
	vector<RemoteCamera> cameras;
	vector<SimpleMirror> mirrors;
	DrawableTexturedEntity<NormalTextureVertexType, ShadowShader> gabenizer;
	SimpleWaterPlane water;
	DrawableTexturedEntity<NormalTextureVertexType, ShadowShader> bath;
	Billboard<TextureVertexType, TextureShader> billboard;
	Billboard<TextureVertexType, TextureShader> billboard2;
	DrawableTexturedEntity<NormalTextureVertexType, ShadowShader> ground;
	DrawableTexturedEntity<NormalTextureVertexType, ShadowShader> wall;
	ColoredParticles particles;
	DrawableBumpyEntity thing;
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	ShadowLight &GetLight(){ return light; }
	void Init(ComPtr<ID3D11Device> device);
	void Render(RenderParams &params);
	void GetRenderBalls(vector<MirrorBall*> &mirrors, vector<RemoteCamera*> &cameraBalls);
};