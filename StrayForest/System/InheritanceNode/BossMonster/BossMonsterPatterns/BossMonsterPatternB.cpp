#include "BossMonsterPatternB.h"
#include "../BossMonster.h"
#include "../../Player/Player.h"
#include "../../MeshFiled.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "BossMonsterPatternC.h"

BossMonsterPatternB::BossMonsterPatternB()
	:	FrameCount_(0)
{

}
void BossMonsterPatternB::Update(BossMonster * _bossmonster)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(SceneGame::GetPlayer()->GetPlayerMatrix()._41, 0.0f, SceneGame::GetPlayer()->GetPlayerPosMatrix()._43);
	D3DXVECTOR3 AxisMove = PlayerPosition - D3DXVECTOR3(_bossmonster->GetPositionMatrix()._41, 0.0f, _bossmonster->GetPositionMatrix()._43);
	D3DXVec3Normalize(&AxisMove, &AxisMove);
	float rotation = atan2f(AxisMove.x, AxisMove.z);
	rotation = rotation + D3DX_PI;
	_bossmonster->Position().y = SceneGame::GetMeshFiled()->GetHeight(_bossmonster->Position());

	//_skinmesh@•à‚«İ’è
	if (FrameCount_ < 85)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(65.3);
		FrameCount_ = 0;
	}

	move = AxisMove * (_bossmonster->GetMoveLowSpeed() + _bossmonster->GetMoveHighSpeed());

	if (_bossmonster->GetLife() < _bossmonster->GetMaxLife() / 2.0f)
	{
		_bossmonster->ChangeBossMonsterMovePattern(new BossMonsterPatternC);
	}

	move.y = 0.0f;
	////ˆÚ“®
	_bossmonster->SetRotation(rotation);
	_bossmonster->SetPosition(move);
}
