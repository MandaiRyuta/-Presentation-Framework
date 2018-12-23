#pragma once

#include "PlayerMoveManager.h"
#include "../../../../Entity/Entity.h"
#include "../../../../GameObjectManager/GameObjectManager.h"
#include "../../../../SkinMeshAnimation/ModelAnim.h"
#include "../../Camera.h"

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

	MOVE_PATTERN AnimPattern_;
	D3DXVECTOR3 position_;

	D3DXVECTOR3 move_;
	D3DXVECTOR3 frontvec_;
	D3DXVECTOR3 rightvec_;
	D3DXVECTOR3 upvec_;

	float movespeed_;
	int counttime_;
	int sleeptime_;
};