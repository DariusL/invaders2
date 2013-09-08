#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <vector>

#include "InstanceEntity.h"
#include "Model.h"

namespace Utils{
	//returns a new array with the contents of the file
	bool ReadFileToArray(std::string file, std::unique_ptr<char> &arr, int &size);
	//return fractional part, ret + trunced = x
	float Trunc(float x, float &trunced);
	std::vector<InstanceEntity> GetGrid(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, std::shared_ptr<Model> model);
}