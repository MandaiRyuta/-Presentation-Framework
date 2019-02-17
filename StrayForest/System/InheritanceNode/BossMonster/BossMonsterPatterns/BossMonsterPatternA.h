#pragma once
#include "BossMonsterPattern.h"
#include "../../../Entity/Entity.h"
#include "../../../colision/SphereColision.h"

class BossMonsterPatternA : public BossMonsterPattern
{
public:
	BossMonsterPatternA();
	~BossMonsterPatternA();
	//@Summary	Update	:	ボスの行動を管理している関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//フレームカウント
};