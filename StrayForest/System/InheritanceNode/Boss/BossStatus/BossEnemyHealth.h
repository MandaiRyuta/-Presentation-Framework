#pragma once

#include "BossEnemyStateManager.h"

class BossEnemyHealth : public BossEnemyStatusManager
{
public:
	BossEnemyHealth() {}
	~BossEnemyHealth() {}
public:
	void Update(Entity::BOSSSTATUS& _bossstatus) override;
private:
	void Damage(double _damage);
	void Heel(double _heel);
private:
	Entity::BOSSSTATUS bossstatus_;
};