#pragma once
#include "../../../../SkinMeshAnimation/ModelAnim.h"

class PlayerMoveManager
{
public:
	PlayerMoveManager() {}
	virtual ~PlayerMoveManager() {}
public:
	virtual void Update(CSkinMesh* _skinmesh,D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation) = 0;
};