#pragma once

#include "PlayerAttackManager.h"

class PlayerAttackPattern01 : public PlayerAttackManager
{
public:
	PlayerAttackPattern01() {}
	~PlayerAttackPattern01() {}
public:
	void Update(Entity::PLAYERSTATUS& _playerstatus, CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation)override;
};