#pragma once

#include "includes.h"


class Camera
{
public:
	Camera();

	void Up(float dist);
	void Right(float dist);
	void Forward(float dist);
	void Yaw(float angle);
	void Pitch(float angle);
	void Roll(float angle);
	void Move(D3DXVECTOR3 vec){ Move(vec.x, vec.y, vec.z); }
	void Move(float x, float y, float z);

	D3DXVECTOR3 GetPosition() const {return pos;}

	void RenderMain();
	const D3DXMATRIX &GetViewMatrix() const { return viewMatrix; }

private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 forward;
	D3DXVECTOR3 up;
	D3DXVECTOR3 right;

	D3DXMATRIX viewMatrix;
	bool modified;
};
