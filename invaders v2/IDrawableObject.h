#pragma once
#include "IDrawable.h"

class IDrawableObject : public IDrawable
{
public:
	IDrawableObject() :IDrawable(){}
	virtual ~IDrawableObject(){}
	IDrawableObject(IDrawableObject && other):IDrawable(std::move(other)){}
protected:
	virtual bool Update(ID3D11DeviceContext *context) = 0;
};