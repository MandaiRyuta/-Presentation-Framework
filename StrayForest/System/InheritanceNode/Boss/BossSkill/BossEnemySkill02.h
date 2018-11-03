#pragma once

#include "BossEnemySkillManager.h"

class BossEnemySkill02 : public BossEnemySkillManager
{
public:
	BossEnemySkill02() {}
	~BossEnemySkill02() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};