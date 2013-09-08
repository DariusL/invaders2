#include "Utils.h"

bool Utils::ReadFileToArray(std::string file, std::unique_ptr<char> &arr, int &size)
{
	std::ifstream stream = std::ifstream(file, std::ios::binary);
	if(!stream.is_open())
		return false;
	stream.seekg(0, stream.end);
	size = stream.tellg();
	stream.seekg(0, stream.beg);
	arr = std::unique_ptr<char>(new char[size]);
	stream.read(arr.get(), size);
	stream.close();
	return true;
}

float Utils::Trunc(float x, float &trunced)
{
	bool neg = x < 0;
	if(neg)
		x = -x;
	trunced = floor(x + 0.5f);
	float frac = x - trunced;
	if(neg)
	{
		frac = -frac;
		trunced = -trunced;
	}
	return frac;
}

std::vector<InstanceEntity> Utils::GetGrid(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, std::shared_ptr<Model> model)
{
	vector<InstanceEntity> ret;
	D3DXVECTOR2 betweenCenters = D3DXVECTOR2(
		(width - 1) * gap.x,
		(height - 1) * gap.y);
	D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);

	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++){
			InstanceEntity object = InstanceEntity(topLeft + D3DXVECTOR3(j * gap.x, i * -gap.y, 0), model->hitbox, 0.0f);
			ret.push_back(object);
		}
	return ret;
}