#pragma once
#include "PlayerStateManager.h"
#include "../../../../Entity/Entity.h"
#include "../../../../GameObjectManager/GameObjectManager.h"
#include "../../../colision/SphereColision.h"

class PlayerState : public PlayerStateManager
{
public:
	explicit PlayerState(Player* _player);
	virtual ~PlayerState();
	virtual void Update(Player* _player);
private:
	SphereColision attackcolision_;
	Entity::SphereColision attackcheck_;
	bool flag_;
	int alphacolor_;
};