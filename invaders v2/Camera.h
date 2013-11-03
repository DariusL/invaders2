#pragma once

#include "includes.h"


class Camera
{
public:
	Camera();

	void SetPostion(D3DXVECTOR3 pos){this->pos = pos;}
	void SetRotation(D3DXVECTOR3 rot){this->rot = rot;}
	void Rotate(D3DXVECTOR3 offset){rot += offset;}
	void Move(D3DXVECTOR3 offset){pos += offset;}

	D3DXVECTOR3 GetPosition(){return pos;}

	virtual void Render();
	virtual void RenderMirror();
	void GetViewMatrix(D3DXMATRIX &matrix){matrix = viewMatrix;}
	void GetMirrorMatrix(D3DXMATRIX &matrix){matrix = mirrorMatrix;}

private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX mirrorMatrix;
};
