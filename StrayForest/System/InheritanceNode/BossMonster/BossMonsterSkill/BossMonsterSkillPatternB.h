#pragma once
#include "BossMonsterSkillPattern.h"

class BossMonsterSkillPatternB : public BossMonsterSkillPattern
{
public:
	BossMonsterSkillPatternB();
	~BossMonsterSkillPatternB();
	void Update(BossMonster* _bossmonster) override;
private:
	int framecounter_;
};