#include "BossEnemyMove.h"
#include "../Player/Player.h"

void BossEnemyMove::Init(D3DXVECTOR3 & _position, D3DXVECTOR3 & _rotation, float & _highspeed, float & _lowspeed, bool & _movestate)
{
	position_ = _position;
	rotation_ = _rotation;
	basic_highspeed_ = _highspeed;
	basic_lowspeed_ = _lowspeed;
	variable_speed_ = 0.0f;
	movestate_ = _movestate;
}

void BossEnemyMove::Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation)
{
	D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(Player::GetPlayerMatrix()._41, Player::GetPlayerMatrix()._42, Player::GetPlayerMatrix()._43);

	D3DXVECTOR3 AxisMove = D3DXVECTOR3(_mtx_position._41, _mtx_position._42, _mtx_position._43) - PlayerPosition;
	D3DXVec3Normalize(&AxisMove, &AxisMove);

	if (movestate_)
	{
		AxisMove * (basic_highspeed_ + variable_speed_);
	}
	else if (!movestate_)
	{
		AxisMove * (basic_lowspeed_ + variable_speed_);
	}
}

void BossEnemyMove::Uninit()
{
	movestate_ = false;
	variable_speed_ = 0.0f;
	basic_highspeed_ = 0.0f;
	basic_lowspeed_ = 0.0f;
}

void BossEnemyMove::MoveStateChange(bool& _movestate)
{
	movestate_ = _movestate;
}

void BossEnemyMove::SpeedChange(bool& _mode, unsigned short& _addspeed)
{
	if (_mode)
	{
		if (ENEMY_MAXHIGHSPEED > variable_speed_)
		{
			variable_speed_ += _addspeed;
		}
		else if (ENEMY_MAXHIGHSPEED <= variable_speed_)
		{
			variable_speed_ += 0.0f;
		}
	}
	else if (!_mode)
	{
		if (ENEMY_MINLOWSPEED < variable_speed_)
		{
			variable_speed_ -= _addspeed;
		}
		else if (ENEMY_MINLOWSPEED >= variable_speed_)
		{
			variable_speed_ -= 0.0f;
		}
	}
}
