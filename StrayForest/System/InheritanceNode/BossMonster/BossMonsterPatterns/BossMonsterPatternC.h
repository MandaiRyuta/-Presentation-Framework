#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternC : public BossMonsterPattern
{
public:
	~BossMonsterPatternC() {}
	void Update(BossMonster* _bossmonster) override;
};