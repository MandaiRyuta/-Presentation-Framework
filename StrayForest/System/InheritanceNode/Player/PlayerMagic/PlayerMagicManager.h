#pragma once
class Player;

class PlayerMagicManager
{
public:
	PlayerMagicManager() {}
	virtual ~PlayerMagicManager() {}
public:
	virtual void Update(Player* _player) = 0;
};

class PlayerMagicNull : public PlayerMagicManager
{
	void Update(Player* _player) override { _player = _player; }
};