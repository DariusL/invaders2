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
	shared_ptr<Model> model;
	D3DXMATRIX moveMatrix;
	shared_ptr<ColorShader> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
public:
	Shooter(void);
	Shooter(D3DXVECTOR2 size, float speed, float fireRate, shared_ptr<Model> model);
	~Shooter(void);

	void SetFireRate(float fireRate){this->fireRate = fireRate;}
	float GetFireRate() const {return fireRate;}

	void Fire(){lastFired = std::clock() / float(CLOCKS_PER_SEC);}
	float GetLastFired() const {return lastFired;}

	bool Init(ComPtr<ID3D11Device>);
	void Render(RenderParams);
private:
	bool InitBuffers(ComPtr<ID3D11Device>);
	void ShutdownBuffers();
	void SetBuffers(ComPtr<ID3D11DeviceContext>);
	bool Update(ComPtr<ID3D11DeviceContext>);

	Shooter& operator=(const Shooter&);
};