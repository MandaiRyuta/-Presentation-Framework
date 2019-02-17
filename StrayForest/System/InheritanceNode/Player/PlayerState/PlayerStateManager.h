#pragma once

class Player;

class PlayerStateManager
{
public:
	PlayerStateManager() {}
	virtual ~PlayerStateManager() {}
	virtual void Update(Player* _player) = 0;
};

class PlayerStateNull : public PlayerStateManager
{
public:
	PlayerStateNull() {}
	virtual ~PlayerStateNull() {}
	virtual void Update(Player* _player) override { _player = _player; }
};