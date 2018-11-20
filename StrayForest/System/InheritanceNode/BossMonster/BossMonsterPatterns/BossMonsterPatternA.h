#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternA : public BossMonsterPattern
{
public:
	~BossMonsterPatternA() {}
	void Update(BossMonster* _bossmonster) override;
private:
	enum BOSSMOVESTATE
	{
		STOP,
		WALK,
		RUN,
		NONE
	};
	BOSSMOVESTATE movestate_;
};