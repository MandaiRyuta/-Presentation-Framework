#include "BossEnemyMove.h"
#include "../../Player/Player.h"
#include "../../MeshFiled.h"
#include "../../../../SceneManager/InheritanceNode/SceneGame.h"

void BossEnemyMove::Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation, Entity::BOSSMOVESTATE& _bossstatus)
{
	bossstatus_ = _bossstatus;

	D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(Player::GetPlayerMatrix()._41, 0.0f, Player::GetPlayerMatrix()._43);
	D3DXVECTOR3 AxisMove = D3DXVECTOR3(_mtx_position._41, 0.0f, _mtx_position._43) - PlayerPosition;
	D3DXVec3Normalize(&AxisMove, &AxisMove);
	
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);

	switch(bossstatus_.movestate_)
	{
	case STOP:
		//_skinmesh ~‚Ü‚Á‚½ó‘Ô
		movespeed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	case WALK:
		//_skinmesh@•à‚«İ’è
		movespeed_ = AxisMove * (bossstatus_.basic_lowspeed_ + bossstatus_.variable_speed_);
		break;
	case RUN:
		//_skinmesh@‘–‚èİ’è
		movespeed_ = AxisMove * (bossstatus_.basic_highspeed_ + bossstatus_.variable_speed_);
		break;
	default:
		break;
	}

	//ˆÚ“®
	position_ += movespeed_;
}