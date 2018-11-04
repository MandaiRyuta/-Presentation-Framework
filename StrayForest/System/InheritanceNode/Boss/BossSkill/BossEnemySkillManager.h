#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../../Entity/Entity.h"

class BossEnemySkillManager
{
public:
	BossEnemySkillManager() {}
	virtual ~BossEnemySkillManager() {}
public:
	virtual void Update(Entity::BOSSSTATUS& _bossstate, CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) = 0;
};