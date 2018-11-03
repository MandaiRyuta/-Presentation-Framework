#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../../Entity/Entity.h"

constexpr double max_mana = 600.0;
constexpr double max_health = 5500.0;
constexpr double max_power = 100.0;

class BossEnemyStatusManager
{
public:
	BossEnemyStatusManager() {}
	~BossEnemyStatusManager() {}
public:
	virtual void Update(Entity::BOSSSTATUS& _bossstatus) = 0;
};