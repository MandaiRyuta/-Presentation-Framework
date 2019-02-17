#include "BossMonsterPatternB.h"
#include "../BossMonster.h"
#include "../../Player/Player.h"
#include "../../MeshFiled.h"
#include "../../../../SceneManager/InheritanceNode/SceneGame.h"
#include "BossMonsterPatternC.h"
#include "../../MyEffekseer/MyEffekseer.h"

BossMonsterPatternB::BossMonsterPatternB()
	:	FrameCount_(0)
{

}

BossMonsterPatternB::~BossMonsterPatternB()
{
	SceneGame::GetBossBuff2Efk()->SetIsDrawing(false);
}

void BossMonsterPatternB::Update(BossMonster * _bossmonster)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(SceneGame::GetPlayer()->GetPlayerMatrix()._41, 0.0f, SceneGame::GetPlayer()->GetPlayerPosMatrix()._43);
	D3DXVECTOR3 AxisMove = PlayerPosition - D3DXVECTOR3(_bossmonster->GetPositionMatrix()._41, 0.0f, _bossmonster->GetPositionMatrix()._43);
	D3DXVec3Normalize(&AxisMove, &AxisMove);
	float rotation = atan2f(AxisMove.x, AxisMove.z);
	rotation = rotation + D3DX_PI;

	SceneGame::GetBossBuff2Efk()->SetIsDrawing(true);
	SceneGame::GetBossBuff2Efk()->SetFrameCount(1.0f);
	SceneGame::GetBossBuff2Efk()->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	SceneGame::GetBossBuff2Efk()->SetPosition(_bossmonster->GetPosition());

	_bossmonster->SetAttackState(false);
	_bossmonster->SetMagicState(false);

	//_skinmesh@•à‚«İ’è
	if (FrameCount_ < 43)
	{
		FrameCount_++;
	}
	else
	{
		//_bossmonster->SetMoveFlagON();
		_bossmonster->GetSkinMesh()->MyChangeAnim(65.3);
		FrameCount_ = 0;
	}

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
	
	if (_bossmonster->GetLife() < _bossmonster->GetMaxLife() * 0.5f)
	{
		_bossmonster->ChangeBossMonsterMovePattern(2,new BossMonsterPatternC);
	}

	move.y = 0.0f;
	////ˆÚ“®
	_bossmonster->SetRotation(rotation);
	_bossmonster->SetPosition(move);
}
