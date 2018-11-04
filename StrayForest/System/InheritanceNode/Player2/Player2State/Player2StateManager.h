#pragma once

class Player2StateManager
{
public:
	Player2StateManager() {}
	virtual ~Player2StateManager() {}
public:
	virtual void Update(bool _hit, bool _skill, bool _power, bool _stamina) = 0;
};