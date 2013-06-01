#include "Player.h"


Player::Player(void)
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Player::Player(D3DXVECTOR3 start)
{
	pos = start;
}

void Player::MoveBy(D3DXVECTOR3 step)
{
	pos += step;
}

Player::~Player(void)
{
}
