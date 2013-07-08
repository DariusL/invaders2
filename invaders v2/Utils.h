#pragma once
#include <memory>
#include <string>
#include <fstream>
using namespace std;

//returns a new array with the contents of the file
void ReadFileToArray(string file, unique_ptr<char> &arr, int &size);