#pragma once
#include "BossMonsterAttackPattern.h"

class BossMonsterAttackPatternA : public BossMonsterAttackPattern
{
public:
	BossMonsterAttackPatternA();
	~BossMonsterAttackPatternA();
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
	bool AttackSetFlag_;
};