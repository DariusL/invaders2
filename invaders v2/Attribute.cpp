#include "includes.h"
#include "Attribute.h"
#include "StringPool.h"
#include "ResourceManager.h"
#include "ColorShader.h"

Attribute::Attribute(e::XMVECTOR pos, e::string text, float width, ColorDrawableEntity &&value, float scale)
:width(width), value(e::move(value)), pos(Utils::FromVector3(pos)), name(Utils::VectorSet(), StringPool::Get().GetString(text), RM::Get().GetShader<ColorShader>(), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), scale)
{
	name.MoveTo(NamePos(name.GetSize().x));
	this->value.MoveTo(ValuePos(this->value.GetSize().x));
}

e::XMVECTOR Attribute::NamePos(float nameWidth)
{
	return Utils::VectorSet(pos.x - (width - nameWidth) / 2.0f, pos.y, pos.z);
}

e::XMVECTOR Attribute::ValuePos(float valueWidth)
{
	return Utils::VectorSet(pos.x + (width - valueWidth) / 2.0f, pos.y, pos.z);
}

void Attribute::Select(bool selected)
{
	float scale = selected ? 1.2f : 1.0f;
	name.SetScale(scale);
	value.SetScale(scale);
}

void Attribute::Render(const RenderParams &params)
{
	value.Render(params);
	name.Render(params);
}

void Attribute::MoveTo(e::XMVECTOR pos)
{
	XMStoreFloat3(&this->pos, pos);
	name.MoveTo(NamePos(name.GetSize().x));
	value.MoveTo(ValuePos(value.GetSize().x));
}