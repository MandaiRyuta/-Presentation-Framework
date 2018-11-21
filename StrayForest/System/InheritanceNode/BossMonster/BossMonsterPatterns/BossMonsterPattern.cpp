#include "BossMonsterPattern.h"
#include "BossMonsterPatternA.h"
#include "../BossMonster.h"

BossMonsterPatternNone::BossMonsterPatternNone()
	: FrameCount_(0)
{
}

void BossMonsterPatternNone::Update(BossMonster * _bossmonster)
{
	if (FrameCount_ > 250)
	{
		_bossmonster->ChangeBossMonsterMovePattern(new BossMonsterPatternA);
	}
	FrameCount_++;
}
