#pragma once
#include "Player2StateManager.h"

class Player2Stamina : public Player2StateManager
{
public:
	Player2Stamina() : Player2StateManager() {}
	~Player2Stamina() {}
public:
	void Update(bool _hit, bool _skill, bool _power, bool _stamina) override;
};