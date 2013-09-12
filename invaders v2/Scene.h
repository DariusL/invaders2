#pragma once
#pragma warning(disable : 4005)
#include "iworld.h"
#include "DrawableShooter.h"
#include "DrawableEntity.h"
class Scene : public IWorld
{
	shared_ptr<DrawableEntity> random;
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);

	Camera &GetCamera(){return camera;}

	bool IsStarted(){return started;}

	bool Init(ComPtr<ID3D11Device>);
	void Render(RenderParams);
};

