#pragma once

#include "BossAttackDamageManager.h"

class BossEnemyAttack01 : public BossAttackDamageManager
{
public:
	BossEnemyAttack01() {}
	~BossEnemyAttack01() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};