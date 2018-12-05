#include "BossMonsterAttackPatternB.h"
#include "../BossMonster.h"

BossMonsterAttackPatternB::BossMonsterAttackPatternB() 
	: FrameCount_(0)
{
}

BossMonsterAttackPatternB::~BossMonsterAttackPatternB()
{
}

void BossMonsterAttackPatternB::Update(BossMonster * _bossmonster)
{
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
