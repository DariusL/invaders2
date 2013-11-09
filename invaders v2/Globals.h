#pragma once
#include "includes.h"

#ifndef NULL
	#define NULL 0
#endif

template <typename T>
using ComVector = std::vector<Microsoft::WRL::ComPtr<T>>;

extern const D3DXVECTOR3 ZeroVec3;
extern const D3DXVECTOR4 ZeroVec4;
extern const D3DXVECTOR3 OneVec3;
extern const D3DXPLANE ZeroPlane;

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct TextureVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 tex;

	TextureVertexType(){}
	TextureVertexType(float x, float y, float z) :position(D3DXVECTOR3(x, y, z)){}
};

struct NormalMappedVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 color;
	D3DXVECTOR2 tex;
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 binormal;

	NormalMappedVertexType(float x, float y, float z) :position(D3DXVECTOR3(x, y, z)), color(0.0f, 1.0f, 1.0f, 1.0f), tangent(0.0f, 0.0f, 0.0f), binormal(0.0f, 0.0f, 0.0f){}
};

struct NormalVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 color;

	NormalVertexType(float x, float y, float z) :position(D3DXVECTOR3(x, y, z)), color(1.0f, 0.0f, 0.0f, 1.0f){}
};

struct InstanceType
{
	D3DXVECTOR3 position;
};

struct MatrixType
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

struct InstancedMatrixType
{
	D3DXMATRIX view;
	D3DXMATRIX projection;
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

struct RenderParams
{
	float brightness;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXVECTOR3 lightPos;
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR3 cameraPos;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	D3DXVECTOR2 waterTranslation;
	float waterScale;
	D3DXMATRIX reflecMatrix;
	D3DXPLANE clipPlane;
};

struct ReflectionType
{
	D3DXMATRIX reflection;
	D3DXMATRIX refraction;
};

struct WaterType
{
	D3DXVECTOR2 waterTranslation;
	float scale;
	float padding;
};

struct BufferInfo
{
	unsigned int offset;
	unsigned int stride;
};