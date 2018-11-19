#pragma once

#include "PlayerDiffenceManager.h"

class Player;

class PlayerDiffence : public PlayerDiffenceManager
{
public:
	explicit PlayerDiffence(Player* _player);
	virtual ~PlayerDiffence();
	virtual void Update(Player* _player);
private:
	PlayerDiffence() {}
private:
	enum DIFFENCE
	{
		START,
		END,
		NONE
	};
	DIFFENCE diffencepattern_;
	int FrameCounter_;
};