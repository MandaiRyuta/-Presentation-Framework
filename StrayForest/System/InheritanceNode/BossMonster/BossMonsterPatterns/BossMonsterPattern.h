#pragma once

class BossMonster;
class SphereColision;

class BossMonsterPattern
{
public:
	virtual ~BossMonsterPattern() {}
	//@Summary	Update	:	ボスの行動を管理している仮想関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	virtual void Update(BossMonster* _bossmoster) = 0;
};

class BossMonsterPatternNone : public BossMonsterPattern
{
public:
	BossMonsterPatternNone();
	virtual ~BossMonsterPatternNone() {}
	//@Summary	Update	:	ボスの行動を管理している関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	virtual void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//フレームカウント
};