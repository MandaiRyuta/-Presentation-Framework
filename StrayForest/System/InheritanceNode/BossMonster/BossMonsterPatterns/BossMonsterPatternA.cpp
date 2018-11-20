#include "BossMonsterPatternA.h"
#include "../BossMonster.h"
#include "../../Player/Player.h"
#include "../../MeshFiled.h"
#include "../../../../SceneManager/InheritanceNode/SceneGame.h"
void BossMonsterPatternA::Update(BossMonster * _bossmonster)
{
	//bossstatus_ = _bossstatus;
	//
	movestate_ = WALK;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(Player::GetPlayerMatrix()._41, 0.0f, Player::GetPlayerMatrix()._43);
	D3DXVECTOR3 AxisMove = PlayerPosition - D3DXVECTOR3(_bossmonster->GetPositionMatrix()._41, 0.0f, _bossmonster->GetPositionMatrix()._43);
	D3DXVec3Normalize(&AxisMove, &AxisMove);
	_bossmonster->Position().y = SceneGame::GetMeshFiled()->GetHeight(_bossmonster->Position());
	
	switch (movestate_)
	{
	case BOSSMOVESTATE::STOP:
		//_skinmesh Ž~‚Ü‚Á‚½ó‘Ô
		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	case BOSSMOVESTATE::WALK:
		//_skinmesh@•à‚«Ý’è
		move = AxisMove * (_bossmonster->GetMoveLowSpeed() + _bossmonster->GetMoveVariableSpeed());
		break;
	case BOSSMOVESTATE::RUN:
		//_skinmesh@‘–‚èÝ’è
		move = AxisMove * (_bossmonster->GetMoveHighSpeed() + _bossmonster->GetMoveVariableSpeed());
		break;
	default:
		break;
	}
	move.y = 0.0f;
	////ˆÚ“®
	_bossmonster->SetPosition(move);
}
