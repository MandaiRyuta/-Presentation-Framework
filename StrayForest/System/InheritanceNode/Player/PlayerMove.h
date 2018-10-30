#pragma once
#include "../../../InputManager/input.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Camera.h"

class PlayerMove
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
	}
	virtual ~PlayerMove() {}
public:
	void Update(CSkinMesh* _skinmesh,D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation);
	bool Uninit() { return true; }
private:
	D3DXQUATERNION rot;
	D3DXVECTOR3 rightvec_;
	D3DXVECTOR3 upvec_;
	D3DXVECTOR3 frontvec_;
	D3DXVECTOR3 move_;
	CInputKeyboard* keyboard_;
	D3DXVECTOR3 position_;
	bool movemode_;
	float movespeed_;
};