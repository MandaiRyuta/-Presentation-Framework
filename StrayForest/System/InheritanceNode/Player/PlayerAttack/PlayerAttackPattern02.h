#pragma once
#include "PlayerAttackManager.h"

class PlayerAttackPattern02 : public PlayerAttackManager
{
public:
	PlayerAttackPattern02() {}
	~PlayerAttackPattern02() {}
public:
	void Update(Entity::PLAYERSTATUS& _playerstatus, CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation)override;
};