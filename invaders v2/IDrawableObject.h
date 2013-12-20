#pragma once
#include "IDrawable.h"

class IDrawableObject : public IDrawable
{
public:
	IDrawableObject() :IDrawable(){}
	IDrawableObject(IDrawableObject && other):IDrawable(std::move(other)){}
protected:
	virtual bool Update(ComPtr<ID3D11DeviceContext>) = 0;
};