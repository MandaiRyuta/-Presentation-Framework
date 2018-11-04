#pragma once

#include "PlayerAttackManager.h"

class PlayerAttackPattern03 : public PlayerAttackManager
{
public:
	PlayerAttackPattern03() {}
	~PlayerAttackPattern03() {}
public:
	void Update(Entity::PLAYERSTATUS& _playerstatus, CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation)override;
};
