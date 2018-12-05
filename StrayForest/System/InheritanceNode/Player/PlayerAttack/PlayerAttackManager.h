#pragma once

class Player;

class PlayerAttackManager
{
public:
	PlayerAttackManager() {}
	virtual ~PlayerAttackManager() {}
public:
	virtual void Update(Player* _player) = 0;
};

class PlayerAttackNull : public PlayerAttackManager
{
	void Update(Player* _player) override { _player = _player; };
};