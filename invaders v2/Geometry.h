#pragma once
#include "includes.h"
#include "BoundingBox.h"
#include "Utils.h"

template<class T>
struct Geometry
{
	std::vector<T> vertices;
	std::vector<int> indices;
	BoundingBox box;
	void Add(const T &vertex);
	void Add(float x, float y, float z);
	Geometry(Geometry &&other);
	Geometry(){}
	void Center();
};

template<class T>
Geometry<T>::Geometry(Geometry &&other)
:vertices(move(other.vertices)),
indices(move(other.indices)),
box(other.box)
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
void Geometry<T>::Center()
{
	auto center = box.GetCenter();
	center.x = -center.x;
	center.y = -center.y;
	center.z = -center.z;
	box.Move(center);
	for (auto &vertex : vertices)
	{
		Utils::VectorAdd(vertex.position, center);
	}
}