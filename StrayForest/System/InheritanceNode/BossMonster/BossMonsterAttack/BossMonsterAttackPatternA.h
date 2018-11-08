#pragma once
#include "BossMonsterAttackPattern.h"

class BossMonsterAttackPatternA : public BossMonsterAttackPattern
{
public:
	BossMonsterAttackPatternA();
	~BossMonsterAttackPatternA();
	void Update(BossMonster* _bossmonster) override;
private:
	int framecounter_;
};