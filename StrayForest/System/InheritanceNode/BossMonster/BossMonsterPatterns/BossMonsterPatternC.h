#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternC : public BossMonsterPattern
{
public:
	BossMonsterPatternC();
	~BossMonsterPatternC();
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
};