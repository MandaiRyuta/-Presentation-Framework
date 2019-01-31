#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternB : public BossMonsterPattern
{
public:
	BossMonsterPatternB();
	~BossMonsterPatternB();
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
};