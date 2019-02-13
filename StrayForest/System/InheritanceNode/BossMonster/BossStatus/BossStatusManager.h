#pragma once

class BossMonster;

class BossStatusManager
{
public:
	explicit BossStatusManager() {}
	virtual ~BossStatusManager() {}
	virtual void Update(BossMonster* _bossmonster) = 0;
	virtual void Draw() = 0;
};

class BossStatusNull : public BossStatusManager
{
public:
	BossStatusNull() {}
	virtual ~BossStatusNull() {}
	virtual void Update(BossMonster* _bossmonster) override { _bossmonster = _bossmonster; }
};