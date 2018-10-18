#pragma once
#include "../../../InputManager/input.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"

class PlayerMove
{
public:
	PlayerMove() 
	{
		position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotation_ = 0.0f;
		frontvec_ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		upvec_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		rightvec_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		OldAxisX_ = false;
		OldAxisZ_ = false;
	}
	virtual ~PlayerMove() {}
public:
	void Update(CSkinMesh* _skinmesh,D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation);
	bool Uninit() { return true; }
private:
	D3DXVECTOR3 rightvec_;
	D3DXVECTOR3 upvec_;
	D3DXVECTOR3 frontvec_;
	D3DXVECTOR3 move_;
	float Speed_;
	bool OldAxisX_;
	bool OldAxisZ_;
	CInputKeyboard* keyboard_;
	D3DXVECTOR3 position_;
	float rotation_;
};