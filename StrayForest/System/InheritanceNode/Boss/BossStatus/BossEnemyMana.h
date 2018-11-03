#pragma once
#include "BossEnemyStateManager.h"

class BossEnemyMana : public BossEnemyStatusManager
{
public:
	BossEnemyMana() {}
	~BossEnemyMana() {}
public:
	void Update(Entity::BOSSSTATUS& _bossstatus) override;
private:
	void UseMagic(double _usemana);
	void UseSkill(double _usemana);
	void AddMana(double _addmana);
private:
	Entity::BOSSSTATUS bossstatus_;
};