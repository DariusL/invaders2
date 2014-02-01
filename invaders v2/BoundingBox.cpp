#include "includes.h"
#include "BoundingBox.h"

using namespace DirectX;

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
	return XMFLOAT3(maxv.x - minv.x, maxv.y - minv.y, maxv.z - minv.z);
}

XMFLOAT3 BoundingBox::GetCenter() const
{
	return XMFLOAT3((minv.x + maxv.x) / 2.0f, (minv.y + maxv.y) / 2.0f, (minv.z + maxv.z) / 2.0f);
}

void BoundingBox::Move(XMFLOAT3 offset)
{
	maxv.x += offset.x;
	maxv.y += offset.y;
	maxv.z += offset.z; 
	minv.x += offset.x;
	minv.y += offset.y;
	minv.z += offset.z;
}