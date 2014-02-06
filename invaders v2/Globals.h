#pragma once
#include "includes.h"
#include "Camera.h"

#ifndef NULL
	#define NULL 0
#endif

namespace e
{
	using namespace std;
	using namespace Microsoft::WRL;
	using namespace DirectX;
}

template <typename T>
using ComVector = std::vector<Microsoft::WRL::ComPtr<T>>;

typedef unsigned int uint;

extern const DirectX::XMFLOAT3 ZeroVec3;
extern const DirectX::XMFLOAT4 ZeroVec4;
extern const DirectX::XMFLOAT3 OneVec3;
extern const DirectX::XMFLOAT2 ZeroVec2;

extern const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> nullResourceView;
extern const Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> nullUnorderedView;
extern const Microsoft::WRL::ComPtr<ID3D11RenderTargetView> nullRenderTargetView;

extern LRESULT CALLBACK MsgRedirect(HWND h, UINT u, WPARAM w, LPARAM l);

struct VertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;

	VertexType(){}
	VertexType(float x, float y, float z, DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)) :position(x, y, z), color(color){}
};

struct NormalVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT3 normal;

	NormalVertexType(float x, float y, float z) :position(x, y, z){}
};

struct InstanceType
{
	DirectX::XMFLOAT3 position;
};

struct ControlCodes
{
	static const int LEFT  = 1 << 0;
	static const int RIGHT = 1 << 1;
	static const int LEFT_AND_RIGHT = LEFT | RIGHT;
	static const int FIRE  = 1 << 2;
	static const int PAUSE = 1 << 3;
	static const int UP    = 1 << 4;
	static const int DOWN  = 1 << 5;
	static const int PLUS  = 1 << 6;
	static const int MINUS = 1 << 7;
	static const int MOVE_UP = 1 << 8;
	static const int MOVE_DOWN = 1 << 9;
	static const int MOVE_LEFT = 1 << 10;
	static const int MOVE_RIGHT = 1 << 11;
	static const int MOVE_FORWARD = 1 << 12;
	static const int MOVE_BACK = 1 << 13;
	static const int ROLL_LEFT = 1 << 14;
	static const int ROLL_RIGHT = 1 << 15;
	static const int EFFECT_1 = 1 << 16;
	static const int EFFECT_2 = 1 << 17;
	static const int EFFECT_3 = 1 << 18;
	static const int EFFECT_4 = 1 << 19;
	static const int ENTER = 1 << 20;
};

enum RESULT
{
	RESULT_CONTINUE,
	RESULT_CLOSE,
	RESULT_UNHANDLED,
	RESULT_QUIT
};

enum POST_PROCESS
{
	POST_PROCESS_NONE,
	POST_PROCESS_CEL,
	POST_PROCESS_BLUR,
	POST_PROCESS_BLOOM
};

__declspec(align(16)) struct RenderParams
{
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
	DirectX::XMFLOAT3 lightPos;
	float brightness;
	DirectX::XMFLOAT4 diffuseColor;
	__declspec(align(16)) ID3D11DeviceContext *context;
	__declspec(align(16)) Camera *camera;
};

struct BufferInfo
{
	unsigned int offset;
	unsigned int stride;
};