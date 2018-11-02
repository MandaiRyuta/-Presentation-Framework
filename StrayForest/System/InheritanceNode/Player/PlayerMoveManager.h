#pragma once
#include "PlayerMove.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"

class PlayerMoveManager
{
public:
	PlayerMoveManager() {}
	~PlayerMoveManager() {}
public:
	void Init();
	void Update(CSkinMesh* _skinmesh,D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation);
	void Uninit();
private:
	PlayerMove* playermove_;
};