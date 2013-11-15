#pragma once

#include "IDrawable.h"
#include "Camera.h"

using namespace std;
using namespace Microsoft::WRL;

class IWorld : public IDrawable
{
protected:
	Camera camera;
	bool started;
	
public:

	virtual bool Start() = 0;
	virtual void Stop() = 0;

	virtual int OnLoop(int input, float frameLength) = 0;

	Camera &GetCamera(){return camera;}

	bool IsStarted(){return started;}

	enum Result
	{
		CONTINUE,
		GAME_OVER,
		NEXT_LEVEL
	};
};