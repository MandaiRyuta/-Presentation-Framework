#include "BossMonsterMagicPatternB.h"
#include "../BossMonster.h"

BossMonsterMagicPatternB::BossMonsterMagicPatternB() 
	: FrameCount_(0)
{
}

BossMonsterMagicPatternB::~BossMonsterMagicPatternB()
{
}

void BossMonsterMagicPatternB::Update(BossMonster * _bossmonster)
{
	if (FrameCount_ < 400)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(31.0);
		FrameCount_ = 0;
	}
}
