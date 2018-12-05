#pragma once

class BossMonster;
class BossMonsterMagicPattern
{
public:
	virtual ~BossMonsterMagicPattern() {}
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossMonsterMagicNone : public BossMonsterMagicPattern
{
public:
	~BossMonsterMagicNone() {}
	void Update(BossMonster* _bossmonster) override {}
};