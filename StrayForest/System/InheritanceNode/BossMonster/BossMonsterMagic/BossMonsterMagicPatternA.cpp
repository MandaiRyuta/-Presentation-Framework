#include "BossMonsterMagicPatternA.h"
#include "../BossMonster.h"

BossMonsterMagicPatternA::BossMonsterMagicPatternA() 
	: FrameCount_(0)
{

}

BossMonsterMagicPatternA::~BossMonsterMagicPatternA()
{
}

void BossMonsterMagicPatternA::Update(BossMonster * _bossmonster)
{
	if (FrameCount_ < 345)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(26.7);
		FrameCount_++;
	}
}
