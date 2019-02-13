#include "BossMonsterPatternA.h"
#include "../BossMonster.h"
#include "../../Player/Player.h"
#include "../../MeshFiled.h"
#include "../../../../SceneManager/InheritanceNode/SceneGame.h"
#include "BossMonsterPatternB.h"
BossMonsterPatternA::BossMonsterPatternA()
	: FrameCount_(0)
{
}

BossMonsterPatternA::~BossMonsterPatternA()
{
}

void BossMonsterPatternA::Update(BossMonster * _bossmonster)
{
	SceneGame::GetBossBuffEfk()->SetIsDrawing(false);

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(SceneGame::GetPlayer()->GetPlayerMatrix()._41, 0.0f, SceneGame::GetPlayer()->GetPlayerPosMatrix()._43);
	D3DXVECTOR3 AxisMove = PlayerPosition - D3DXVECTOR3(_bossmonster->GetPositionMatrix()._41, 0.0f, _bossmonster->GetPositionMatrix()._43);
	D3DXVec3Normalize(&AxisMove, &AxisMove);
	float rotation = atan2f(AxisMove.x, AxisMove.z);
	rotation = rotation + D3DX_PI;

	_bossmonster->Position().y = SceneGame::GetMeshFiled()->GetHeight(_bossmonster->Position());

	//_skinmesh@•à‚«İ’è
	if (FrameCount_ < 70)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->SetMoveFlagON();
		_bossmonster->GetSkinMesh()->MyChangeAnim(63.3);
		FrameCount_ = 0;
	}

	//if (!colisioncheck)
	if (!_bossmonster->GetMoveColisionCheck())
	{
		if (!_bossmonster->GetknockbackFlag())
		{
			move = _bossmonster->GetAxisMove() * (_bossmonster->GetMoveMiddleSpeed() + _bossmonster->GetMoveVariableSpeed());
		}
		else
		{
			move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}


	if (_bossmonster->GetLife() < _bossmonster->GetMaxLife() * 0.75f)
	{
		//_bossmonster->ChangeBossMonsterAttackPattern(new BossMonsterAttackPatternB);
		_bossmonster->ChangeBossMonsterMovePattern(1,new BossMonsterPatternB);
	}

	move.y = 0.0f;
	////ˆÚ“®
	_bossmonster->SetRotation(rotation);
	_bossmonster->SetPosition(move);
}
