#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"

class BossEnemyDeffenceManager
{
public:
	BossEnemyDeffenceManager() {}
	~BossEnemyDeffenceManager() {}
public:
	virtual void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) = 0;
};