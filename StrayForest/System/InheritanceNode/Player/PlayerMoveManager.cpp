#include "PlayerMoveManager.h"

void PlayerMoveManager::Init()
{
	playermove_ = new PlayerMove;
}

void PlayerMoveManager::Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation)
{
	playermove_->Update(_skinmesh,_mtx_position, _mtx_rotation);
}

void PlayerMoveManager::Uninit()
{
}
