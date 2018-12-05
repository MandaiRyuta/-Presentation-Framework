#include "BossMonsterSkillPatternA.h"
#include "../BossMonster.h"

BossMonsterSkillPatternA::BossMonsterSkillPatternA()
	: framecounter_(0)
{
}

BossMonsterSkillPatternA::~BossMonsterSkillPatternA()
{
}

void BossMonsterSkillPatternA::Update(BossMonster * _bossmonster)
{
	if (framecounter_ < 300)
	{
		framecounter_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(9.0);
		framecounter_ = 0;
	}
}
