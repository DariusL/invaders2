#include "includes.h"
#include "Utils.h"

namespace Utils
{
	bool ReadFileToArray(std::wstring file, std::unique_ptr<char> &arr, UINT &size)
	{
		std::ifstream stream = std::ifstream(file, std::ios::binary);
		if (!stream.is_open())
			return false;
		stream.seekg(0, stream.end);
		size = (UINT)stream.tellg();
		stream.seekg(0, stream.beg);
		arr = std::unique_ptr<char>(new char[size]);
		stream.read(arr.get(), size);
		stream.close();
		return true;
	}

	float Trunc(float x, float &trunced)
	{
		bool neg = x < 0;
		if (neg)
			x = -x;
		trunced = floor(x + 0.5f);
		float frac = x - trunced;
		if (neg)
		{
			frac = -frac;
			trunced = -trunced;
		}
		return frac;
	}

	void ShowMessageBox(std::wstring text, std::wstring title)
	{
		MessageBox(NULL, text.c_str(), title.c_str(), MB_OK);
	}

	e::XMFLOAT4 PlaneFromPointAndRot(e::XMFLOAT3 point, e::XMFLOAT3 rot, bool reverse)
	{
		using namespace e;
		XMVECTOR normal = XMVectorSet(0.0f, 0.0f, (reverse ? 1.0f : -1.0f), 0.0f);
		XMMATRIX matrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		e::XMFLOAT3 temp;
		//normale pasukta, kad butu statmena plokstumai
		XMStoreFloat3(&temp, XMVector3Transform(normal, matrix));
		//sudaroma plokstumos lygtis
		return XMFLOAT4(temp.x, temp.y, temp.z, -(temp.x*point.x + temp.y*point.y + temp.z*point.z));
	}

	e::XMFLOAT2 GetVec2(float value)
	{
		return e::XMFLOAT2(value, value);
	}

	e::XMFLOAT3 GetVec3(float value)
	{
		return e::XMFLOAT3(value, value, value);
	}

	e::XMFLOAT4 GetVec4(float value)
	{
		return e::XMFLOAT4(value, value, value, value);
	}

	void VectorAdd(e::XMFLOAT3 &target, const e::XMFLOAT3 &off)
	{
		target.x += off.x;
		target.y += off.y;
		target.z += off.z;
	}

	e::XMVECTOR VectorFill(float f)
	{
		return e::XMVectorSet(f, f, f, f);
	}

	e::XMVECTOR VectorSet()
	{
		return e::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	}

	e::XMVECTOR VectorSet(float x)
	{
		return e::XMVectorSet(x, 0.0f, 0.0f, 0.0f);
	}

	e::XMVECTOR VectorSet(float x, float y)
	{
		return e::XMVectorSet(x, y, 0.0f, 0.0f);
	}

	e::XMVECTOR VectorSet(float x, float y, float z)
	{
		return e::XMVectorSet(x, y, z, 0.0f);
	}

	e::XMFLOAT3 FromVector3(e::XMVECTOR vec)
	{
		e::XMFLOAT3 ret;
		e::XMStoreFloat3(&ret, vec);
		return ret;
	}

	int HighestBitSet(int a)
	{
		int mask = 1 << 31;
		int bit = 31;
		while (!(a & mask) && bit > 0)
		{
			a <<= 1;
			bit--;
		}
		return bit;
	}
}