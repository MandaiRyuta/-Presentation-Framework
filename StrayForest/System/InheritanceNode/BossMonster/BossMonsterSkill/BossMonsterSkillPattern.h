#pragma once

class BossMonster;
class BossMonsterSkillPattern
{
public:
	virtual ~BossMonsterSkillPattern() {}
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossMonsterSkillNull : public BossMonsterSkillPattern
{
	void Update(BossMonster* _bossmonster) override {}
};