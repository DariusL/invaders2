#include "includes.h"
#include "Attribute.h"
#include "StringPool.h"
#include "ResourceManager.h"
#include "ColorShader.h"

Attribute::Attribute(e::XMVECTOR pos, e::string text, float width, e::XMFLOAT4 color, ColorDrawableEntity &&value, float scale)
:width(width), value(e::move(value)), pos(Utils::FromVector3(pos)), name(Utils::VectorSet(), StringPool::Get().GetString(text), RM::Get().GetShader<ColorShader>(), color, scale)
{
	name.MoveTo(NamePos(name.GetSize().x));
	value.MoveTo(ValuePos(value.GetSize().x));
}

e::XMVECTOR Attribute::NamePos(float nameWidth)
{
	return Utils::VectorSet(pos.x - (width - nameWidth) / 2.0f, pos.y, pos.z);
}

e::XMVECTOR Attribute::ValuePos(float valueWidth)
{
	return Utils::VectorSet(pos.x + (width - valueWidth) / 2.0f, pos.y, pos.z);
}