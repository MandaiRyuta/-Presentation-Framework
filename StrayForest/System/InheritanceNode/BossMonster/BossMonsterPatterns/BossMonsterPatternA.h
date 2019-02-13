#pragma once
#include "BossMonsterPattern.h"
#include "../../../Entity/Entity.h"
#include "../../../colision/SphereColision.h"

class BossMonsterPatternA : public BossMonsterPattern
{
public:
	BossMonsterPatternA();
	~BossMonsterPatternA();
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
};