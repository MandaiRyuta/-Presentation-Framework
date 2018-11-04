#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"
#include "PlayerMoveManager.h"
#include "../../Camera.h"

class CInputKeyboard;

class PlayerMove : public PlayerMoveManager
{
public:
	PlayerMove() 
	{
		position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//frontvec_ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		upvec_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		rightvec_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		frontvec_ = CCamera::GetAt() - CCamera::GetEye();
		frontvec_.y = 0.0f;
		movespeed_ = 1.2f;
		D3DXVec3Normalize(&frontvec_, &frontvec_);
		AnimPattern_ = WALK;
		counttime_ = 0;
		sleeptime_ = 0;
	}
	virtual ~PlayerMove() {}
public:
	void Update(CSkinMesh* _skinmesh,D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation) override;
private:
	enum MOVE_PATTERN
	{
		STATE,
		WALK,
		RUN
	};
	MOVE_PATTERN AnimPattern_;
	D3DXVECTOR3 rightvec_;
	D3DXVECTOR3 upvec_;
	D3DXVECTOR3 frontvec_;
	D3DXVECTOR3 move_;
	CInputKeyboard* keyboard_;
	D3DXVECTOR3 position_;
	bool movemode_;
	float movespeed_;
	int counttime_;
	int sleeptime_;
};