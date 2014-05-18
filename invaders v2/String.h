#pragma once
#include "includes.h"
#include "IDrawableObject.h"
#include "Model.h"
#include "ColorShader.h"
#include "ResourceManager.h"
#include "AppendableGeometry.h"

using namespace DirectX;

template<class vt>
class String : public AppendableGeometry<vt>
{
public:
	String(e::string text, float gap = 0.1f);
	String(String &&other);
	virtual ~String(){}
};

template<class vt>
String<vt>::String(e::string text, float gap)
:AppendableGeometry(gap)
{
	ResourceManager &rm = RM::Get();
	for (auto &c : text)
	{
		if (c == ' ')
		{
			XMFLOAT3 p = box.GetMax();
			p.x += 0.6f;
			box.Add(p);
		}
		else
		{
			this->operator+=(rm.GetLetter(c));
		}
	}
	Center();
}

template<class vt>
String<vt>::String(String &&other)
:AppendableGeometry(move(other))
{
}