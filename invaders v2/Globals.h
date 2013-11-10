#pragma once
#include "includes.h"

using namespace DirectX;

#ifndef NULL
	#define NULL 0
#endif

template <typename T>
using ComVector = std::vector<Microsoft::WRL::ComPtr<T>>;

extern const XMFLOAT3 ZeroVec3;
extern const XMFLOAT4 ZeroVec4;
extern const XMFLOAT3 OneVec3;
extern const XMFLOAT2 ZeroVec2;

struct VertexType
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

struct TextureVertexType
{
	XMFLOAT3 position;
	XMFLOAT2 tex;

	TextureVertexType(){}
	TextureVertexType(float x, float y, float z) :position(XMFLOAT3(x, y, z)){}
};

struct NormalMappedVertexType
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT4 color;
	XMFLOAT2 tex;
	XMFLOAT3 tangent;
	XMFLOAT3 binormal;

	NormalMappedVertexType(float x, float y, float z) :position(XMFLOAT3(x, y, z)), color(0.0f, 1.0f, 1.0f, 1.0f), tangent(0.0f, 0.0f, 0.0f), binormal(0.0f, 0.0f, 0.0f){}
};

struct NormalVertexType
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT4 color;

	NormalVertexType(float x, float y, float z) :position(XMFLOAT3(x, y, z)), color(1.0f, 0.0f, 0.0f, 1.0f){}
};

struct InstanceType
{
	XMFLOAT3 position;
};

struct MatrixType
{
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

struct InstancedMatrixType
{
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
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
};

__declspec(align(16)) struct RenderParams
{
	XMMATRIX reflecMatrix;
	XMMATRIX view;
	XMMATRIX projection;
	XMFLOAT3 lightPos;
	float brightness;
	XMFLOAT4 diffuseColor;
	XMFLOAT3 cameraPos;
	float waterScale;
	XMFLOAT4 clipPlane;
	XMFLOAT2 waterTranslation;
	__declspec(align(16)) Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
};

struct ReflectionType
{
	XMFLOAT4X4 reflection;
	XMFLOAT4X4 refraction;
};

struct WaterType
{
	XMFLOAT2 waterTranslation;
	float scale;
	float padding;
};

struct BufferInfo
{
	unsigned int offset;
	unsigned int stride;
};