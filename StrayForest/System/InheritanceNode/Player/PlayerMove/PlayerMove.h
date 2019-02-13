#pragma once

#include "PlayerMoveManager.h"
#include "../../../../Entity/Entity.h"

class PlayerMove : public PlayerMoveManager
{
public:
	PlayerMove();
	virtual ~PlayerMove();
	virtual void Update(Player* _player);
private:
	enum MOVE_PATTERN
	{
		STATE,
		WALK,
		RUN,
		ROLL,
		NONE
	};

	double stickx_;
	double sticky_;
	MOVE_PATTERN AnimPattern_;
	D3DXVECTOR3 position_;

	D3DXVECTOR3 move_;
	D3DXVECTOR3 frontvec_;
	D3DXVECTOR3 rightvec_;
	D3DXVECTOR3 upvec_;
	float oldmodelrotation_;
	float movespeed_;
	int counttime_;
	int sleeptime_;
	bool rollflag_;
	bool runflag_;
};