#pragma once

#include "PlayerDiffenceManager.h"

class PlayerDiffence : public PlayerDiffenceManager
{
public:
	explicit PlayerDiffence(Player* _player);
	virtual ~PlayerDiffence();
	virtual void Update(Player* _player);
private:
	PlayerDiffence() {}
private:
	int FrameCounter_;
};