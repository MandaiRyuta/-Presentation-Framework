#pragma once

#include "BossEnemyMagicManager.h"

class BossEnemyMagic03 : public BossEnemyMagicManager
{
public:
	BossEnemyMagic03() {}
	~BossEnemyMagic03() {}
public:
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) override;
};