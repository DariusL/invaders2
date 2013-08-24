#pragma once

#include <memory>

#include "entity.h"
#include "IDrawableObject.h"
#include "Model.h"
#include "ColorShader.h"

using namespace std;
class Shooter : public Entity, public IDrawableObject
{
	//fiziks
	//per second
	float fireRate;
	float lastFired;

	//grafiks
	Model *model;
	D3DXMATRIX moveMatrix;
	unique_ptr<ColorShader> shader;

	unique_ptr<ID3D11Buffer, COMDeleter> vertexBuffer;
	unique_ptr<ID3D11Buffer, COMDeleter> indexBuffer;
	unique_ptr<ID3D11Buffer, COMDeleter> matrixBuffer;
public:
	Shooter(void);
	Shooter(D3DXVECTOR2 size, float speed, float fireRate, Model *model);
	~Shooter(void);

	void SetFireRate(float fireRate){this->fireRate = fireRate;}
	float GetFireRate() const {return fireRate;}

	void Fire(){lastFired = std::clock() / float(CLOCKS_PER_SEC);}
	float GetLastFired() const {return lastFired;}

	bool Init(ID3D11Device*, HWND);
	void Render(ID3D11DeviceContext*, D3DXMATRIX);
private:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void SetBuffers(ID3D11DeviceContext*);
	bool Update(ID3D11DeviceContext*);

	Shooter& operator=(const Shooter&);
};