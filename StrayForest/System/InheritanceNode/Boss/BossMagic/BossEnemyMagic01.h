#pragma once

#include "BossEnemyMagicManager.h"

class BossEnemyMagic01 : public BossEnemyMagicManager
{
public:
	BossEnemyMagic01() {}
	~BossEnemyMagic01() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};