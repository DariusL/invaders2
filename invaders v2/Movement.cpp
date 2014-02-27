#include "includes.h"
#include "Movement.h"

Movement::Movement(e::XMFLOAT3 start, e::XMFLOAT3 end, int length)
:start(start), end(end), length(length), startTime(clock())
{
	using namespace e;
	auto vec = (XMLoadFloat3(&end) - XMLoadFloat3(&start)) / (float)length;
	XMStoreFloat3(&off, vec);
}

Movement::Movement(e::XMVECTOR start, e::XMVECTOR end, int length)
:length(length), startTime(clock())
{
	using namespace e;
	XMStoreFloat3(&this->start, start);
	XMStoreFloat3(&this->end, end);
	auto vec = (end - start) / (float)length;
	XMStoreFloat3(&off, vec);
}

e::XMVECTOR Movement::GetPos()
{
	using namespace e;
	if (IsOver())
		return e::XMLoadFloat3(&end);
	float count = (float)(clock() - startTime);
	return e::XMLoadFloat3(&start) + e::XMLoadFloat3(&off) * count;
}

bool Movement::IsOver()
{
	return startTime + length < clock();
}

e::XMVECTOR Movement::GetDir()
{
	return e::XMVector3Normalize(e::XMLoadFloat3(&off));
}