#pragma once

class BossMonster;
class BossMonsterAttackPattern
{
public:
	virtual ~BossMonsterAttackPattern() {}
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossMonsterAttackNone : public BossMonsterAttackPattern
{
	void Update(BossMonster* _bossmonster) override {}
};