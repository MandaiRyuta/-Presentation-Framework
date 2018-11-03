#pragma once

#include "BossEnemyMoveManager.h"

class BossEnemyMove : public BossEnemyMoveManager
{
public:
	BossEnemyMove() 
	{
		position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	~BossEnemyMove() {}
public:
	void Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation, Entity::BOSSMOVESTATE& _bossstatus) override;
private:
	enum MOVESTATE
	{
		STOP,
		WALK,
		RUN,
		NONE
	};
	D3DXVECTOR3 position_;
	D3DXVECTOR3 movespeed_;
	Entity::BOSSMOVESTATE bossstatus_;
};