#pragma once
#include "Globals.h"
#include <vector>
using namespace std;
struct Model
{
	vector<VertexType> vertices;
	int vertexCount;
	vector<int> indices;
	int indexCount;
};