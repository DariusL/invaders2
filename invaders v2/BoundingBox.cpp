#include "includes.h"
#include "BoundingBox.h"

using namespace DirectX;
BoundingBox::BoundingBox()
{
}


void BoundingBox::Add(const XMFLOAT3 &vert)
{
	if (empty)
	{
		minv = maxv = vert;
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

XMFLOAT3 BoundingBox::GetSize()
{
	return XMFLOAT3(maxv.x - minv.x, maxv.y - minv.y, maxv.z - minv.z);
}