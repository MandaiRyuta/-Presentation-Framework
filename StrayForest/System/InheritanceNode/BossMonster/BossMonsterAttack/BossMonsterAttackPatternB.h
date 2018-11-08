#pragma once

#include "BossMonsterAttackPattern.h"

class BossMonsterAttackPatternB : public BossMonsterAttackPattern
{
public:
	BossMonsterAttackPatternB();
	~BossMonsterAttackPatternB();
	void Update(BossMonster* _bossmonster) override;
private:
	int framecounter_;
};