#pragma once
#include "../../../../Entity/Entity.h"

class PlayerStateManager
{
public:
	PlayerStateManager() {}
	virtual ~PlayerStateManager() {}
public:
	virtual void Update(Entity::PLAYERSTATUS& _playerstate) = 0;
};