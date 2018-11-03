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
		//_skinmesh 止まった状態
		movespeed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	case WALK:
		//_skinmesh　歩き設定
		movespeed_ = AxisMove * (bossstatus_.basic_lowspeed_ + bossstatus_.variable_speed_);
		break;
	case RUN:
		//_skinmesh　走り設定
		movespeed_ = AxisMove * (bossstatus_.basic_highspeed_ + bossstatus_.variable_speed_);
		break;
	default:
		break;
	}

	//移動
	position_ += movespeed_;
}