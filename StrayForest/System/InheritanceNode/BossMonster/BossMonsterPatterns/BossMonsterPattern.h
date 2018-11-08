#pragma once

class BossMonster;

class BossMonsterPattern
{
public:
	virtual ~BossMonsterPattern() {}
	virtual void Update(BossMonster* _bossmoster) = 0;
};

class BossMonsterPatternNone : public BossMonsterPattern
{
public:
	virtual ~BossMonsterPatternNone() {}
	virtual void Update(BossMonster* _bossmonster) override;
};