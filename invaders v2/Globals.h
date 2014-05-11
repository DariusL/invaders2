#pragma once
#include "includes.h"
#include "Camera.h"

#ifndef NULL
	#define NULL 0
#endif

template <typename T>
using ComVector = e::vector<e::ComPtr<T>>;

using uint = unsigned int;
using ulong = unsigned long long;

extern const e::XMFLOAT3 ZeroVec3;
extern const e::XMFLOAT4 ZeroVec4;
extern const e::XMFLOAT3 OneVec3;
extern const e::XMFLOAT2 ZeroVec2;

extern const e::XMFLOAT4 Gray;

extern const e::ComPtr<ID3D11ShaderResourceView> nullResourceView;
extern const e::ComPtr<ID3D11UnorderedAccessView> nullUnorderedView;
extern const e::ComPtr<ID3D11RenderTargetView> nullRenderTargetView;

extern LRESULT CALLBACK MsgRedirect(HWND h, UINT u, WPARAM w, LPARAM l);

struct VertexType
{
	e::XMFLOAT3 position;

	VertexType(){}
	VertexType(float x, float y, float z) :position(x, y, z){}
};

struct NormalVertexType
{
	e::XMFLOAT3 position;
	e::XMFLOAT4 color;
	e::XMFLOAT3 normal;

	NormalVertexType(float x, float y, float z) :position(x, y, z){}
};

struct InstanceType
{
	e::XMFLOAT3 position;
	float padding;
	e::XMFLOAT4 color;
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
	RESULT_QUIT_APP,
	RESULT_QUIT_TO_MAIN
};

enum POST_PROCESS
{
	POST_PROCESS_NONE,
	POST_PROCESS_CEL,
	POST_PROCESS_BLUR,
	POST_PROCESS_BLOOM
};

enum GAME_EVENT
{
	GAME_EVENT_ENEMY_DEATH,
	GAME_EVENT_PLAYER_BULLET_CREATE,
	GAME_EVENT_ENEMY_CREATE,
	GAME_EVENT_ENEMY_BULLET_CREATE
};

enum UPGRADE_EVENT
{
	UPGRADE_EVENT_HEALTH_SET,
	UPGRADE_EVENT_MAX_HEALTH_SET,
	UPGRADE_EVENT_WEPON_PERIOD_SET,
	UPGRADE_EVENT_WEPON_DMG_SET,
	UPGRADE_EVENT_WEPON_COUNT_SET,
	UPGRADE_EVENT_EXP_SET
};

__declspec(align(16)) struct RenderParams
{
	e::XMMATRIX view;
	e::XMMATRIX projection;
	e::XMFLOAT3 lightPos;
	float brightness;
	e::XMFLOAT4 diffuseColor;
	__declspec(align(16)) ID3D11DeviceContext *context;
	__declspec(align(16)) Camera *camera;
	__declspec(align(16)) bool gray;
};