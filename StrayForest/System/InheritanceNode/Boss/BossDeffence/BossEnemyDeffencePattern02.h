#pragma once

#include "BossEnemyDeffenceManager.h"

class BossEnemyDeffencePattern02 : public BossEnemyDeffenceManager
{
public:
	BossEnemyDeffencePattern02() {}
	~BossEnemyDeffencePattern02() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};