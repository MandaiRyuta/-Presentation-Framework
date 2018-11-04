#pragma once
#include "PlayerStateManager.h"

class PlayerStamina : public PlayerStateManager
{
public:
	PlayerStamina() {}
	~PlayerStamina() {}
public:
	void Update(Entity::PLAYERSTATUS& _playerstate) override;
private:
	double stamina_;
};