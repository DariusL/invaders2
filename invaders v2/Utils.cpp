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

	XMFLOAT4 PlaneFromPointAndRot(XMFLOAT3 point, XMFLOAT3 rot, bool reverse)
	{
		XMVECTOR normal = XMVectorSet(0.0f, 0.0f, (reverse ? 1.0f : -1.0f), 0.0f);
		XMMATRIX matrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		XMFLOAT3 temp;
		XMStoreFloat3(&temp, XMVector3Transform(normal, matrix));
		return XMFLOAT4(temp.x, temp.y, temp.z, -(temp.x*point.x + temp.y*point.y + temp.z*point.z));
	}

	XMFLOAT2 GetVec2(float value)
	{
		return XMFLOAT2(value, value);
	}

	XMFLOAT3 GetVec3(float value)
	{
		return XMFLOAT3(value, value, value);
	}

	XMFLOAT4 GetVec4(float value)
	{
		return XMFLOAT4(value, value, value, value);
	}
}