#include "includes.h"
#include "Utils.h"

namespace Utils
{
	bool ReadFileToArray(wstring file, std::unique_ptr<char> &arr, UINT &size)
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

	std::vector<InstanceEntity> GetGrid(int width, int height, XMFLOAT3 center, XMFLOAT2 gap, ColorModel &model)
	{
		AssertBool(false, L"GetGrid got deimplemented");
		vector<InstanceEntity> ret;
		/*XMFLOAT2 betweenCenters = XMFLOAT2(
			(width - 1) * gap.x,
			(height - 1) * gap.y);
		XMFLOAT3 topLeft = XMFLOAT3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);

		for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++){
			ret.emplace_back(topLeft + XMFLOAT3(j * gap.x, i * -gap.y, 0), model.hitbox, 0.0f);
		}*/
		return ret;
	}

	void ShowMessageBox(wstring text, wstring title)
	{
		MessageBox(NULL, text.c_str(), title.c_str(), MB_OK);
	}

	XMFLOAT4 PlaneFromPointAndRot(XMFLOAT3 point, XMFLOAT3 rot)
	{
		XMFLOAT3 n(0.0f, 0.0f, -1.0f);
		XMMATRIX matrix;
		XMFLOAT3 temp;
		matrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		XMStoreFloat3(&temp, XMVector3Transform(XMLoadFloat3(&n), matrix));
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