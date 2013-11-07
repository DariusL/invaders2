#pragma once
#include "IDrawable.h"

class IDrawableObject : public IDrawable
{
public:
	IDrawableObject():IDrawable(){}
	IDrawableObject(IDrawableObject && other):IDrawable(std::forward<IDrawableObject>(other)){}
protected:
	virtual void InitBuffers(ComPtr<ID3D11Device>) = 0;
	virtual void SetBuffers(ComPtr<ID3D11DeviceContext>) = 0;
	virtual bool Update(ComPtr<ID3D11DeviceContext>) = 0;
};