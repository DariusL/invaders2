#pragma once
#include "includes.h"
#include "BoundingBox.h"

template<class T>
struct Geometry
{
	std::vector<T> vertices;
	std::vector<int> indices;
	BoundingBox box;
	void Add(const T &vertex);
	void Add(float x, float y, float z);
	Geometry &operator+=(const Geometry &other);
	Geometry(Geometry &&other);
	Geometry(){}
	void Center();
};

template<class T>
Geometry<T>::Geometry(Geometry &&other)
:vertices(move(other.vertices)),
indices(move(other.indices)),
box(move(other.box))
{
	other.box = BoundingBox();
}

template<class T>
void Geometry<T>::Add(const T &vertex)
{
	vertices.push_back(vertex);
	box.Add(vertex.position);
}

template<class T>
void Geometry<T>::Add(float x, float y, float z)
{
	vertices.emplace_back(x, y, z);
	box.Add(vertices.back().position);
}

template<class T>
Geometry<T> &Geometry<T>::operator+=(const Geometry<T> &other)
{
	if (other.vertices.size() > 0)
	{
		uint size = vertices.size();
		uint oisize = other.indices.size();
		uint ovsize = other.vertices.size();
		float gap = 0.2f;
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

template<class T>
void Geometry<T>::Center()
{
	auto center = box.GetCenter();
	center.x = -center.x;
	center.y = -center.y;
	center.z = -center.z;
	box.Move(center);
	for (auto &vertex : vertices)
	{
		vertex.position.x += center.x;
		vertex.position.y += center.y;
		vertex.position.z += center.z;
	}
}