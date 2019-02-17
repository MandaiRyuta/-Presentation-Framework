#pragma once
#include "BossMonsterAttackPattern.h"

class BossMonsterAttackPatternA : public BossMonsterAttackPattern
{
public:
	BossMonsterAttackPatternA();
	~BossMonsterAttackPatternA();
	//@Summary	Update	:	ボスの通常攻撃の更新用の関数
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//フレームカウント
};