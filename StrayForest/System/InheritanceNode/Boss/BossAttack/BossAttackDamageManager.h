#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"

class BossAttackDamageManager
{
public:
	BossAttackDamageManager() {}
	virtual ~BossAttackDamageManager() {}
public:
	virtual void Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation) = 0;
};