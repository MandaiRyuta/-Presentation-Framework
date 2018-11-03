#pragma once

#include "BossEnemyMagicManager.h"

class BossEnemyMagic02 : public BossEnemyMagicManager
{
public:
	BossEnemyMagic02() {}
	~BossEnemyMagic02() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};