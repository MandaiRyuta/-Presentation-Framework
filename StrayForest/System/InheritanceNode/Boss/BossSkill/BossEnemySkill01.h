#pragma once

#include "BossEnemySkillManager.h"

class BossEnemySkill01 : public BossEnemySkillManager
{
public:
	BossEnemySkill01() {}
	~BossEnemySkill01() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};