#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../../Entity/Entity.h"

class PlayerAttackManager
{
public:
	PlayerAttackManager() {}
	virtual ~PlayerAttackManager() {}
public:
	virtual void Update(Entity::PLAYERSTATUS& _playerstatus, CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation) = 0;
};