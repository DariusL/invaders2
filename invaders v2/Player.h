#pragma once
#pragma warning(disable : 4005)
#include <D3D11.h>
#include <D3DX10math.h>
class Player
{
public:
	Player();
	Player(D3DXVECTOR3 start);
	~Player(void);

	D3DXVECTOR3 getPos(){return pos;}
	void MoveBy(D3DXVECTOR3 step);
private:
	D3DXVECTOR3 pos;
};

