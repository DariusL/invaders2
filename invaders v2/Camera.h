#pragma once
#pragma warning(disable : 4005)

#include <d3dx10math.h>

class Camera
{
public:
	Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX viewMatrix;
};
