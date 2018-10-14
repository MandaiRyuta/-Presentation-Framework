#include "PlayerMove.h"
#include "../../../Renderer/GameManager.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../MeshFiled.h"

void PlayerMove::Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation)
{
	keyboard_ = GameManager::GetKeyboard();
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);

	if (keyboard_->GetKeyPress(DIK_LSHIFT))
	{
		runspeed_ = 2.0f;
	}
	else
	{
		runspeed_ = 0.0f;
	}

	if (keyboard_->GetKeyPress(DIK_W))
	{
		position_.z += movespeed_ + runspeed_;
	}
	if (keyboard_->GetKeyPress(DIK_S))
	{
		position_.z += -(movespeed_ + runspeed_);
	}
	if (keyboard_->GetKeyPress(DIK_A))
	{
		position_.x += -(movespeed_ + runspeed_);
	}
	if (keyboard_->GetKeyPress(DIK_D))
	{
		position_.x += movespeed_ + runspeed_;
	}

	D3DXMatrixTranslation(&_mtx_position, position_.x, position_.y, position_.z);

	if (keyboard_->GetKeyPress(DIK_Q))
	{
		rotation_ += -D3DXToRadian(rolingspeed_);
	}
	if (keyboard_->GetKeyPress(DIK_E))
	{
		rotation_ += D3DXToRadian(rolingspeed_);
	}
	D3DXMatrixRotationYawPitchRoll(&_mtx_rotation, rotation_, 0.0f,0.0f);
}