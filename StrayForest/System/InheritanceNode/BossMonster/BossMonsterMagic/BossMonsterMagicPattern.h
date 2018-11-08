#pragma once

class BossMonster;
class BossMonsterMagicPattern
{
public:
	virtual ~BossMonsterMagicPattern() {}
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossMonsterMagicNull : public BossMonsterMagicPattern
{
	void Update(BossMonster* _bossmonster) override {}
};