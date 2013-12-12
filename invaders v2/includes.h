#pragma once

//target Win7
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0601

#pragma warning(push)
#pragma warning(disable : 4005)
#include <stdint.h>
#pragma warning(pop)

#include <wrl\client.h>
#include <vector>
#include <list>
#include <Windows.h>
#include <sstream>
#include <memory>
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <utility>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <algorithm>
#include <functional>