#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternC : public BossMonsterPattern
{
public:
	BossMonsterPatternC();
	~BossMonsterPatternC();
	//@Summary	Update	:	ボスの行動を管理している関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//フレームカウント
};