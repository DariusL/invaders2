#pragma once
#include "Globals.h"
#include <memory>
using namespace std;
struct Model
{
	unique_ptr<VertexType[]> vertices;
	int vertexCount;
	unique_ptr<int[]> indices;
	int indexCount;
};