#pragma once
#include "../../../SkinMeshAnimation/ModelAnim.h"

class BossEnemyMove;
class BossEnemyMoveManager
{
public:
	BossEnemyMoveManager() {}
	~BossEnemyMoveManager() {}
public:
	void Init(D3DXVECTOR3& _position, D3DXVECTOR3& _rotation, float& _highspeed, float& _lowspeed, bool& _movestate);
	void Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation);
	void Uninit();

	void MoveStateChange(bool& _movestate);
	void SpeedChange(bool& _mode, unsigned short& _addspeed);
private:
	BossEnemyMove* BossMove_;
};