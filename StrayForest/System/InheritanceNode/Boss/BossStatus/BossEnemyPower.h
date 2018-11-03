#pragma once
#include "BossEnemyStateManager.h"

class BossEnemyPower : public BossEnemyStatusManager
{
public:
	BossEnemyPower() {}
	~BossEnemyPower() {}
public:
	void Update(Entity::BOSSSTATUS& _bossstatus) override;
private:
	void PowerUP(double _addPower);
	void PowerDown(double _decreasePower);
private:
	Entity::BOSSSTATUS bossstatus_;
};