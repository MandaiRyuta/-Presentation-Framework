#include "BossMonsterPatternC.h"
#include "../BossMonster.h"
#include  "../../Player/Player.h"
#include "../../MeshFiled.h"
#include "../../../../SceneManager/InheritanceNode/SceneGame.h"

BossMonsterPatternC::BossMonsterPatternC()
	: FrameCount_(0)
{
}

BossMonsterPatternC::~BossMonsterPatternC()
{
	SceneGame::GetBossBuffEfk()->SetIsDrawing(false);
}

void BossMonsterPatternC::Update(BossMonster * _bossmonster)
{
	SceneGame::GetBossBuff2Efk()->SetIsDrawing(false);

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(SceneGame::GetPlayer()->GetPlayerMatrix()._41, 0.0f, SceneGame::GetPlayer()->GetPlayerPosMatrix()._43);
	D3DXVECTOR3 AxisMove = PlayerPosition - D3DXVECTOR3(_bossmonster->GetPositionMatrix()._41, 0.0f, _bossmonster->GetPositionMatrix()._43);
	D3DXVec3Normalize(&AxisMove, &AxisMove);
	float rotation = atan2f(AxisMove.x, AxisMove.z);
	rotation = rotation + D3DX_PI;
	_bossmonster->Position().y = SceneGame::GetMeshFiled()->GetHeight(_bossmonster->Position());
	
	SceneGame::GetBossBuffEfk()->SetIsDrawing(true);
	SceneGame::GetBossBuffEfk()->SetFrameCount(1.0f);
	SceneGame::GetBossBuffEfk()->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	SceneGame::GetBossBuffEfk()->SetPosition(_bossmonster->GetPosition());

	if (FrameCount_ < 85)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(65.3);
		FrameCount_ = 0;
	}

	move = AxisMove * (_bossmonster->GetMoveVariableSpeed() + _bossmonster->GetMoveVariableSpeed());


	move.y = 0.0f;

	_bossmonster->SetRotation(rotation);
	_bossmonster->SetPosition(move);
}
