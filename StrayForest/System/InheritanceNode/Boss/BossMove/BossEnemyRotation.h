#pragma once

#include "BossEnemyMoveManager.h"

class BossEnemyRotation : public BossEnemyMoveManager
{
public:
	BossEnemyRotation() {}
	virtual ~BossEnemyRotation() {}
public:
	void Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation, Entity::BOSSMOVESTATE& _bossstatus) override;
};