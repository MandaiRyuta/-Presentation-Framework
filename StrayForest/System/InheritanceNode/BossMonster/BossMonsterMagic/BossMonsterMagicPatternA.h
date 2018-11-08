#pragma once
#include "BossMonsterMagicPattern.h"

class BossMonsterMagicPatternA : public BossMonsterMagicPattern
{
public:
	BossMonsterMagicPatternA();
	~BossMonsterMagicPatternA();
	void Update(BossMonster* _bossmonster) override;
private:
	int framecount_;
};