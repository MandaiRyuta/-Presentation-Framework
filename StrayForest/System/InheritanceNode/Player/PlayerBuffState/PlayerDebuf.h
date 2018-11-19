#pragma once

#include "PlayerBuffStateManager.h"


class PlayerDebuf : public PlayerBuffStateManager
{
public:
	explicit PlayerDebuf(Player* _player);
	virtual ~PlayerDebuf();
	void Update(Player* _player) override;
private:
	PlayerDebuf() {}
private:
	int FrameCounter_;
};