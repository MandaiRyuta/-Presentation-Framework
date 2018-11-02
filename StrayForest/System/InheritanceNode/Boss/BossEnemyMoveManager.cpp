#include "BossEnemyMoveManager.h"
#include "BossEnemyMove.h"

void BossEnemyMoveManager::Init(D3DXVECTOR3& _position, D3DXVECTOR3& _rotation, float& _highspeed, float& _lowspeed, bool& _movestate)
{
	BossMove_ = new BossEnemyMove;
	BossMove_->Init(_position, _rotation, _highspeed, _lowspeed, _movestate);
}

void BossEnemyMoveManager::Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation)
{
	BossMove_->Update(_skinmesh, _mtx_position, _mtx_rotation);
}

void BossEnemyMoveManager::Uninit()
{
	BossMove_->Uninit();
	delete BossMove_;
}

void BossEnemyMoveManager::MoveStateChange(bool& _movestate)
{
	BossMove_->MoveStateChange(_movestate);
}

void BossEnemyMoveManager::SpeedChange(bool& _mode, unsigned short& _addspeed)
{
	BossMove_->SpeedChange(_mode, _addspeed);
}
