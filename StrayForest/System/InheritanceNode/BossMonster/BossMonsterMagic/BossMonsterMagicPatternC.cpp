#include "BossMonsterMagicPatternC.h"
#include "../BossMonster.h"

BossMonsterMagicPatternC::BossMonsterMagicPatternC() 
	: FrameCount_(0)
{
}

BossMonsterMagicPatternC::~BossMonsterMagicPatternC()
{
}

void BossMonsterMagicPatternC::Update(BossMonster * _bossmonster)
{
	if (FrameCount_ < 280)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(37.0);
		FrameCount_ = 0;
	}
}
