#pragma once
#include "includes.h"
#include "IDrawable.h"
#include "Input.h"
#include "GameEntity.h"

class MenuItem : public virtual IDrawable
{
public:
	virtual ~MenuItem(){}
	virtual bool Loop(InputType input) = 0;
	virtual void Delay() = 0;
	virtual void Select(bool selected) = 0;
	virtual void MoveTo(e::XMVECTOR pos) = 0;
};