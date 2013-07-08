#include "Utils.h"

void ReadFileToArray(string file, unique_ptr<char> &arr, int &size)
{
	ifstream stream = ifstream(file, ios::binary);
	stream.seekg(0, stream.end);
	size = stream.tellg();
	stream.seekg(0, stream.beg);
	arr = unique_ptr<char>(new char[size]);
	stream.read(arr.get(), size);
	stream.close();
}