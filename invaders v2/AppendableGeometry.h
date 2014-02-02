#pragma once
#include "includes.h"
#include "Geometry.h"

template<class T>
class AppendableGeometry : public Geometry<T>
{
	float gap;
public:
	AppendableGeometry(float gap) :gap(gap){}
	AppendableGeometry(AppendableGeometry &&other) :gap(other.gap), Geometry(move(other)){}
	AppendableGeometry &operator+=(const Geometry &other);
};

template<class T>
AppendableGeometry<T> &AppendableGeometry<T>::operator+=(const Geometry<T> &other)
{
	if (other.vertices.size() > 0)
	{
		uint size = vertices.size();
		uint oisize = other.indices.size();
		uint ovsize = other.vertices.size();
		float width = box.GetSize().x;
		for (uint i = 0; i < ovsize; i++)
		{
			auto vertex = other.vertices[i];
			vertex.position.x += width + gap;
			Add(vertex);
		}
		for (uint i = 0; i < oisize; i++)
			indices.push_back(size + other.indices[i]);
	}
	return *this;
}