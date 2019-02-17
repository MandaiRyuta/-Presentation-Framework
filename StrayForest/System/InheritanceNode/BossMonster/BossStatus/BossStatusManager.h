#pragma once

class BossMonster;

class BossStatusManager
{
public:
	explicit BossStatusManager() {}
	virtual ~BossStatusManager() {}
	//@Summary	Update	:	ボスのステータス情報の更新用の仮想関数
	//@ParamName	=	"_bossmonster"	:	ボス情報
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossStatusNull : public BossStatusManager
{
public:
	BossStatusNull() {}
	virtual ~BossStatusNull() {}
	//@Summary	Update	:	ボスのステータス情報の更新処理用の関数
	//@ParamName	=	"_bossmonster"	:	ボス情報
	virtual void Update(BossMonster* _bossmonster) override { _bossmonster = _bossmonster; }
};