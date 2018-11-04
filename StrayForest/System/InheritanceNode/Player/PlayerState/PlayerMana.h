#pragma once
#include "PlayerStateManager.h"

class PlayerMana : public PlayerStateManager
{
public:
	PlayerMana() : PlayerStateManager() {}
	~PlayerMana() {}
public:
	void Update(Entity::PLAYERSTATUS& _playerstatus);
private:
	Entity::PLAYERSTATUS playerstatus_;
};