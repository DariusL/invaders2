#pragma once
#pragma warning(disable : 4005)

#include <d3dx10math.h>

class Camera
{
public:
	Camera();

	void SetPosition(const D3DXVECTOR3& pos);
	void SetRotation(float yaw, float pitch);

	D3DXVECTOR3 GetPosition(){return pos;}

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	D3DXVECTOR3 pos;
	float yaw;
	float pitch;
	D3DXMATRIX viewMatrix;
};
