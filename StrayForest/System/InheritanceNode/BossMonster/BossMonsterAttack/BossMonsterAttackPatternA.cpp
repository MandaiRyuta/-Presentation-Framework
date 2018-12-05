#include "BossMonsterAttackPatternA.h"
#include "../BossMonster.h"

BossMonsterAttackPatternA::BossMonsterAttackPatternA() 
	: FrameCount_(0)
	, AttackSetFlag_(false)
{
}

BossMonsterAttackPatternA::~BossMonsterAttackPatternA()
{
}

void BossMonsterAttackPatternA::Update(BossMonster * _bossmonster)
{
	if (!AttackSetFlag_)
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(5.2);
		AttackSetFlag_ = true;
	}
	if (FrameCount_ < 200)
	{
		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(5.2);
		FrameCount_ = 0;
	}
}
