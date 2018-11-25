#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternA : public BossMonsterPattern
{
public:
	BossMonsterPatternA();
	~BossMonsterPatternA() {}
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
};