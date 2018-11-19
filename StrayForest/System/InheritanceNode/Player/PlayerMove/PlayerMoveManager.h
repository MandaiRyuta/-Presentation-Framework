#pragma once

class Player;

class PlayerMoveManager
{
public:
	PlayerMoveManager() {}
	virtual ~PlayerMoveManager() {}
	virtual void Update(Player* _player) = 0;
};

class PlayerMoveNull : public PlayerMoveManager
{
public:
	PlayerMoveNull() {}
	virtual ~PlayerMoveNull() {}
	virtual void Update(Player* _player) override {}
};