#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../../Entity/Entity.h"

class BossEnemyMoveManager
{
public:
	BossEnemyMoveManager() {}
	~BossEnemyMoveManager() {}
public:
	virtual void Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation, Entity::BOSSMOVESTATE& _bossstatus) = 0;
};