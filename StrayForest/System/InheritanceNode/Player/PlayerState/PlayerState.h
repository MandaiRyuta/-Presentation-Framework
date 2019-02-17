#pragma once
#include "PlayerStateManager.h"
#include "../../../../Entity/Entity.h"
#include "../../../colision/SphereColision.h"

class PlayerState : public PlayerStateManager
{
public:
	explicit PlayerState(Player* _player);
	virtual ~PlayerState();
	virtual void Update(Player* _player);
private:
	bool damegeflag_;
	int damegeframe_;
	int damegecount_;
	float enemyweponscale_;
	Entity::MATRIX3D LeftHand_;
	D3DXVECTOR3 playerhitpos_;
	float playerhitscale_;
	D3DXVECTOR3 set;
	SphereColision attackcolision_;
	Entity::SphereColision attackcheck_;
	bool flag_;
	int alphacolor_;
	int frame_;
	bool attackflag_;
};