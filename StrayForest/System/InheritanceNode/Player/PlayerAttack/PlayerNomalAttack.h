#pragma once
#include "PlayerAttackManager.h"

class PlayerNomalAttack : public PlayerAttackManager
{
public:
	explicit PlayerNomalAttack(Player* _player);
	virtual ~PlayerNomalAttack() {}
	void Update(Player* _player) override;
private:
	PlayerNomalAttack() {}
private:
	enum ATTACKPATTERN
	{
		ATTACK01,
		ATTACK02,
		ATTACK03,
		MAX_ATTACK
	};
	ATTACKPATTERN attackpattern_;
	int FrameCounter_;
};