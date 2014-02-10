#include "includes.h"
#include "MenuItem.h"
#include "DrawableShooter.h"

class GameWorld : public IDrawable
{
	DrawableShooter player;
public:
	GameWorld(e::XMVECTOR pos);
	void Loop(float frame);
	void Render(const RenderParams &params);
};