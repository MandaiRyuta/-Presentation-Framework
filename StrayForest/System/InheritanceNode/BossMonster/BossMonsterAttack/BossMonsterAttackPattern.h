#pragma once

class BossMonster;
class BossMonsterAttackPattern
{
public:
	virtual ~BossMonsterAttackPattern() {}
	//@Summary	Update	:	ボスの通常攻撃の更新用の仮想関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossMonsterAttackNone : public BossMonsterAttackPattern
{
	//@Summary	Update	:	ボスの通常攻撃の更新用の関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	void Update(BossMonster* _bossmonster) override {}
};