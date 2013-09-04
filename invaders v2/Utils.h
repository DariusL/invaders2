#pragma once
#include <memory>
#include <string>
#include <fstream>

namespace Utils{
	//returns a new array with the contents of the file
	void ReadFileToArray(std::string file, std::unique_ptr<char> &arr, int &size);
	//return fractional part, ret + trunced = x
	float Trunc(float x, float &trunced);
}