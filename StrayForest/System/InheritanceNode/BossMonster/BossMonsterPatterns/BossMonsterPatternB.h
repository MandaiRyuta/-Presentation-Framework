#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternB : public BossMonsterPattern
{
public:
	~BossMonsterPatternB() {}
	void Update(BossMonster* _bossmonster) override;
};