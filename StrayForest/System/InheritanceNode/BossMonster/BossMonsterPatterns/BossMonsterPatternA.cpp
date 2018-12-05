#include "BossMonsterPatternA.h"
#include "../BossMonster.h"
#include "../../Player/Player.h"
#include "../../MeshFiled.h"
#include "../../../../SceneManager/InheritanceNode/SceneGame.h"
#include "BossMonsterPatternB.h"
#include "../BossMonsterAttack/BossMonsterAttackPatternB.h"
BossMonsterPatternA::BossMonsterPatternA()
	: FrameCount_(0)
{
}

void BossMonsterPatternA::Update(BossMonster * _bossmonster)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(Player::GetPlayerMatrix()._41, 0.0f, Player::GetPlayerMatrix()._43);
	D3DXVECTOR3 AxisMove = PlayerPosition - D3DXVECTOR3(_bossmonster->GetPositionMatrix()._41, 0.0f, _bossmonster->GetPositionMatrix()._43);
	D3DXVec3Normalize(&AxisMove, &AxisMove);
	float rotation = atan2f(AxisMove.x, AxisMove.z);
	rotation = rotation + D3DX_PI;

	_bossmonster->Position().y = SceneGame::GetMeshFiled()->GetHeight(_bossmonster->Position());

	//_skinmesh　歩き設定
	if (FrameCount_ < 140)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(63.3);
		FrameCount_ = 0;
	}

	move = AxisMove * (_bossmonster->GetMoveLowSpeed() + _bossmonster->GetMoveVariableSpeed());


	if (_bossmonster->GetLife() < _bossmonster->GetMaxLife() / 1.5f)
	{
		_bossmonster->ChangeBossMonsterAttackPattern(new BossMonsterAttackPatternB);
		_bossmonster->ChangeBossMonsterMovePattern(new BossMonsterPatternB);
	}

	move.y = 0.0f;
	////移動
	_bossmonster->SetRotation(rotation);
	_bossmonster->SetPosition(move);
}
