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
	void Move(D3DXVECTOR3 offset);

	D3DXVECTOR3 GetPosition(){return pos;}

	virtual void RenderMain();
	virtual void RenderMirror();
	void GetViewMatrix(D3DXMATRIX &matrix){matrix = viewMatrix;}
	void GetMirrorMatrix(D3DXMATRIX &matrix){matrix = mirrorMatrix;}

private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 forward;
	D3DXVECTOR3 up;
	D3DXVECTOR3 right;

	D3DXMATRIX viewMatrix;
	D3DXMATRIX mirrorMatrix;
};
