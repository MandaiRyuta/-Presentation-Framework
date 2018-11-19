#pragma once
class Player;

class PlayerDiffenceManager
{
public:
	PlayerDiffenceManager() {}
	virtual ~PlayerDiffenceManager() {}
public:
	virtual void Update(Player* _player) = 0;
};

class PlayerDiffenceNull : public PlayerDiffenceManager
{
	void Update(Player* _player) override {}
};

