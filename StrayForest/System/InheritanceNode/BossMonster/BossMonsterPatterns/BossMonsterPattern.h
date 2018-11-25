#pragma once

class BossMonster;
class SphereColision;

class BossMonsterPattern
{
public:
	virtual ~BossMonsterPattern() {}
	virtual void Update(BossMonster* _bossmoster) = 0;
};

class BossMonsterPatternNone : public BossMonsterPattern
{
public:
	BossMonsterPatternNone();
	virtual ~BossMonsterPatternNone() {}
	virtual void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
};