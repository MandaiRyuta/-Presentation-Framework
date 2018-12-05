#include "BossMonsterAttackPatternC.h"
#include "../BossMonster.h"

BossMonsterAttackPatternC::BossMonsterAttackPatternC()
	: FrameCount_(0)
{
}

BossMonsterAttackPatternC::~BossMonsterAttackPatternC()
{
}

void BossMonsterAttackPatternC::Update(BossMonster * _bossmonster)
{
	if (FrameCount_ < 150)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(23.5);
		FrameCount_++;
	}
}
