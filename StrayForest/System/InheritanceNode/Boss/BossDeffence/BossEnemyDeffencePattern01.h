#pragma once

#include "BossEnemyDeffenceManager.h"

class BossEnemyDeffencePattern01 : public BossEnemyDeffenceManager
{
public:
	BossEnemyDeffencePattern01() {}
	~BossEnemyDeffencePattern01() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};