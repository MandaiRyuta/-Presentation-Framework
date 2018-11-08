#pragma once
#include "BossMonsterSkillPattern.h"

class BossMonsterSkillPatternA : public BossMonsterSkillPattern
{
public:
	BossMonsterSkillPatternA();
	~BossMonsterSkillPatternA();
	void Update(BossMonster* _bossmonster) override;
private:
	int framecounter_;
};