#include "BossMonsterPattern.h"
#include "BossMonsterPatternA.h"
#include "BossMonsterPatternB.h"
#include "../BossMonster.h"

BossMonsterPatternNone::BossMonsterPatternNone()
	: FrameCount_(0)
{
}

void BossMonsterPatternNone::Update(BossMonster * _bossmonster)
{
	if (FrameCount_ > 250)
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(63.3);
		_bossmonster->ChangeBossMonsterMovePattern(new BossMonsterPatternB);
	}
	FrameCount_++;
}
