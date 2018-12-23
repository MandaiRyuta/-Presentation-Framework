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
		STATE,
		ATTACK01,
		ATTACK02,
		ATTACK03,
		NONE
	};
	ATTACKPATTERN attackpattern_;
	int FrameCounter_;
	float AtkAddEffect01_;
};