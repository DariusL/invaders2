#pragma once
#include <memory>
#include <string>
#include <sstream>
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
	void ShowMessageBox(wstring text, wstring title);
}

#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define __WFILE__ WIDE1(__FILE__)

#ifndef _DEBUG
#define Assert(x)   if (x != S_OK) \
                        { \
							wstringstream stream; \
							stream << hex << x; \
							Utils::ShowMessageBox(L"Error number 0x" + stream.str(), __WFILE__ + wstring(L": ") + to_wstring(__LINE__)); \
							exit(-1); \
                        }
#else
#define Assert(x)   if (x != S_OK) \
						{ \
							wstringstream stream; \
							stream << hex << x; \
							Utils::ShowMessageBox(L"Error number 0x" + stream.str(), __WFILE__ + wstring(L": ") + to_wstring(__LINE__)); \
							DebugBreak(); \
						}
#endif