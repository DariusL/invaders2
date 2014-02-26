#include "includes.h"
#include "Movement.h"

Movement::Movement(e::XMFLOAT3 start, e::XMFLOAT3 end, e::chrono::milliseconds length)
:start(start), end(end), length(length), startTime(e::chrono::system_clock::now())
{
	using namespace e;
	float count = (float)length.count();
	auto vec = (XMLoadFloat3(&end) - XMLoadFloat3(&start)) / count;
	XMStoreFloat3(&off, vec);
}

e::XMVECTOR Movement::GetPos()
{
	using namespace e;
	if (IsOver())
		return e::XMLoadFloat3(&end);
	float count = (float)e::chrono::duration_cast<e::chrono::milliseconds>(Clock::now() - startTime).count();
	return e::XMLoadFloat3(&start) + e::XMLoadFloat3(&off) * count;
}

bool Movement::IsOver()
{
	return startTime + length < e::chrono::system_clock::now();
}