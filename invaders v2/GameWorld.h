#include "includes.h"
#include "MenuItem.h"
#include "ColorDrawableEntity.h"

class GameWorld : public IDrawable
{
	ColorDrawableEntity player;
public:
	GameWorld(e::XMVECTOR pos);
	void Loop(float frame);
	void Render(const RenderParams &params);
};