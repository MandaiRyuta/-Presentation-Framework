#pragma once
#include "PlayerStateManager.h"

class PlayerPowerDown : public PlayerStateManager
{
public:
	PlayerPowerDown() : PlayerStateManager() {}
	~PlayerPowerDown() {}
public:
	void Update(Entity::PLAYERSTATUS& _playerstate) override;
private:
	double power_;
};