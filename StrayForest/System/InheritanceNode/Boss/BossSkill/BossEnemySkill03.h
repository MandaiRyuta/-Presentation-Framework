#pragma once

#include "BossEnemySkillManager.h"

class BossEnemySkill03 : public BossEnemySkillManager
{
public:
	BossEnemySkill03() {}
	~BossEnemySkill03() {}
public:
	void Update(Entity::BOSSSTATUS& _bossstate, CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};