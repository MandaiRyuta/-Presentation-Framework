#pragma once
#include "PlayerStateManager.h"

class PlayerPowerUP : public PlayerStateManager
{
public:
	PlayerPowerUP() {}
	~PlayerPowerUP() {}
public:
	void Update(Entity::PLAYERSTATUS& _playerstate) override;
private:
	double power_;
};