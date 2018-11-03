#pragma once

#include "BossAttackDamageManager.h"

class BossEnemyAttack02 : public BossAttackDamageManager
{
public:
	BossEnemyAttack02() {}
	~BossEnemyAttack02() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};