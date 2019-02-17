#include "BossMonsterAttackPatternA.h"
#include "../BossMonster.h"

BossMonsterAttackPatternA::BossMonsterAttackPatternA() 
	: FrameCount_(0)
{
}

BossMonsterAttackPatternA::~BossMonsterAttackPatternA()
{
}

void BossMonsterAttackPatternA::Update(BossMonster * _bossmonster)
{
	if (!_bossmonster->GetAttackState())
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(5.2);
		_bossmonster->SetAttackState(true);
		_bossmonster->SetMagicState(false);
	}
	if (FrameCount_ < 100)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(5.2);
		FrameCount_ = 0;
	}
}
