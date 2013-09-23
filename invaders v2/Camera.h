#pragma once

#include "includes.h"


class Camera
{
public:
	Camera();

	void SetRotation(float yaw, float pitch, float r);

	D3DXVECTOR3 GetPosition(){return pos;}

	virtual void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	D3DXVECTOR3 pos;
	float yaw;
	float pitch;
	float r;
	D3DXMATRIX viewMatrix;
};
