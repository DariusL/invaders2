#include "Utils.h"

void Utils::ReadFileToArray(std::string file, std::unique_ptr<char> &arr, int &size)
{
	std::ifstream stream = std::ifstream(file, std::ios::binary);
	stream.seekg(0, stream.end);
	size = stream.tellg();
	stream.seekg(0, stream.beg);
	arr = std::unique_ptr<char>(new char[size]);
	stream.read(arr.get(), size);
	stream.close();
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