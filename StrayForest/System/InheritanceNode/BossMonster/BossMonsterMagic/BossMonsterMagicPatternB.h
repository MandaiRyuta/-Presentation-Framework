#pragma once
#include "BossMonsterMagicPattern.h"

class BossMonsterMagicPatternB : public BossMonsterMagicPattern
{
public:
	BossMonsterMagicPatternB();
	~BossMonsterMagicPatternB();
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
};