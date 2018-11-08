#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternA : public BossMonsterPattern
{
public:
	~BossMonsterPatternA() {}
	void Update(BossMonster* _bossmonster) override;
};