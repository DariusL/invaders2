#include "includes.h"
#include "Utils.h"

namespace Utils
{
	bool ReadFileToArray(std::string file, std::unique_ptr<char> &arr, UINT &size)
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

	std::vector<InstanceEntity> GetGrid(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, ColorModel &model)
	{
		vector<InstanceEntity> ret;
		D3DXVECTOR2 betweenCenters = D3DXVECTOR2(
			(width - 1) * gap.x,
			(height - 1) * gap.y);
		D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);

		for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++){
			InstanceEntity object = InstanceEntity(topLeft + D3DXVECTOR3(j * gap.x, i * -gap.y, 0), model.hitbox, 0.0f);
			ret.push_back(object);
		}
		return ret;
	}

	void ShowMessageBox(wstring text, wstring title)
	{
		MessageBox(NULL, text.c_str(), title.c_str(), MB_OK);
	}

	D3DXPLANE PlaneFromPointAndRot(D3DXVECTOR3 point, D3DXVECTOR3 rot)
	{
		D3DXVECTOR3 normal(0.0f, 0.0f, -1.0f);
		D3DXMATRIX matrix;
		D3DXVECTOR4 temp;
		D3DXMatrixRotationYawPitchRoll(&matrix, rot.x, rot.y, rot.z);
		D3DXVec3Transform(&temp, &normal, &matrix);
		D3DXPLANE ret(temp.x, temp.y, temp.z, -(temp.x*point.x + temp.y*point.y, temp.z*point.z));
		return ret;
	}
}