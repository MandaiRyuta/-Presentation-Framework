#pragma once

#include "PlayerBuffStateManager.h"

class PlayerBuff : public PlayerBuffStateManager
{
public:
	explicit PlayerBuff(Player* _player);
	virtual ~PlayerBuff();
	virtual void Update(Player* _player);
private:
	PlayerBuff() {}
private:
	int FrameCounter_;
};