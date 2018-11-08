#pragma once
#include "BossMonsterMagicPattern.h"

class BossMonsterMagicPatternC : public BossMonsterMagicPattern
{
public:
	BossMonsterMagicPatternC();
	~BossMonsterMagicPatternC();
	void Update(BossMonster* _bossmonster) override;
private:
	int framecount_;
};