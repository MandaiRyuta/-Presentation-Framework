#pragma once

#include "BossAttackDamageManager.h"

class BossEnemyAttack03 : public BossAttackDamageManager
{
public:
	BossEnemyAttack03() {}
	~BossEnemyAttack03() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};