#pragma once

#include "../../../SkinMeshAnimation/ModelAnim.h"

class BossEnemyStatusManager
{
public:
	BossEnemyStatusManager() {}
	~BossEnemyStatusManager() {}
public:
	void Init();
	void Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation);
	void Uninit();
private:

};