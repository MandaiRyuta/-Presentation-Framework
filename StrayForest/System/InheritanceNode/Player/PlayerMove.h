#pragma once
#include "../../../InputManager/input.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"

class PlayerMove
{
public:
	PlayerMove() 
	{
		movespeed_ = 1.0f;
		runspeed_ = 0.0f;
		rolingspeed_ = 3.0f;
		position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotation_ = 0.0f;
	}
	virtual ~PlayerMove() {}
public:
	void Update(CSkinMesh* _skinmesh,D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation);
	bool Uninit() { return true; }
private:
	CInputKeyboard* keyboard_;
	D3DXVECTOR3 position_;
	float rotation_;
	float runspeed_;
	float movespeed_;
	float rolingspeed_;
};