#pragma once
class Player;

class PlayerBuffStateManager
{
public:
	PlayerBuffStateManager() {}
	virtual ~PlayerBuffStateManager() {}
public:
	virtual void Update(Player* _player) = 0;
};

class PlayerbuffNull : public PlayerBuffStateManager
{
	void Update(Player* _player) override { _player = _player; }
};