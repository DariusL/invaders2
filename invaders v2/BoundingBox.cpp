#include "includes.h"
#include "BoundingBox.h"
#include "Utils.h"
using namespace e;

void BoundingBox::Add(const XMFLOAT3 &vert)
{
	if (empty)
	{
		minv = maxv = vert;
		empty = false;
	}
	else
	{
		minv.x = min(minv.x, vert.x);
		minv.y = min(minv.y, vert.y);
		minv.z = min(minv.z, vert.z);

		maxv.x = max(maxv.x, vert.x);
		maxv.y = max(maxv.y, vert.y);
		maxv.z = max(maxv.z, vert.z);
	}
}

XMFLOAT3 BoundingBox::GetSize() const
{
	return empty ? ZeroVec3 : XMFLOAT3(maxv.x - minv.x, maxv.y - minv.y, maxv.z - minv.z);
}

XMFLOAT3 BoundingBox::GetCenter() const
{
	return empty ? ZeroVec3 : XMFLOAT3((minv.x + maxv.x) / 2.0f, (minv.y + maxv.y) / 2.0f, (minv.z + maxv.z) / 2.0f);
}

void BoundingBox::Move(XMFLOAT3 offset)
{
	Utils::VectorAdd(maxv, offset);
	Utils::VectorAdd(minv, offset);
}