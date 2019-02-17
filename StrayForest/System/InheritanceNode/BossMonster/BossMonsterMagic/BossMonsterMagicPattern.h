#pragma once

class BossMonster;
class BossMonsterMagicPattern
{
public:
	virtual ~BossMonsterMagicPattern() {}
	//@Summary	Update	:	ボスの魔法攻撃の更新用の仮想関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossMonsterMagicNone : public BossMonsterMagicPattern
{
public:
	~BossMonsterMagicNone() {}
	//@Summary	Update	:	ボスの魔法攻撃の更新用の関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	void Update(BossMonster* _bossmonster) override {}
};