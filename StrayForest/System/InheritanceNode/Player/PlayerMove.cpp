#include "PlayerMove.h"
#include "../../../Renderer/GameManager.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../MeshFiled.h"
#include "../Camera.h"
void PlayerMove::Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation)
{
	keyboard_ = GameManager::GetKeyboard();
	position_ = CCamera::GetAt();
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);
	frontvec_ = position_ - CCamera::GetEye();
	frontvec_.y = 0.0f;
	D3DXVec3Normalize(&frontvec_, &frontvec_);
	//rotation_ = D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(180.0f);

	if (keyboard_->GetKeyPress(DIK_LSHIFT))
	{

	}
	else
	{

	}
	
	move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (keyboard_->GetKeyPress(DIK_W))
	{
		if (rotation_ <= D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(180.0f))
		{
			rotation_ += D3DXToRadian(5.0f);
		}
		else if (rotation_ > D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(180.0f))
		{
			rotation_ -= D3DXToRadian(5.0f);
		}
		move_ = position_ - CCamera::GetEye();
		D3DXVec3Normalize(&move_, &move_);
		D3DXMATRIX moverot;
		D3DXMatrixRotationAxis(&moverot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(0.0f));
		D3DXVec3TransformNormal(&move_, &move_, &moverot);
	}
	if (keyboard_->GetKeyPress(DIK_S))
	{
		OldAxisZ_ = true;
		if (OldAxisX_)
		{
			rotation_ = D3DXToRadian(-90.0f);
			OldAxisX_ = false;
		}
		if (rotation_ <= D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(0.0f))
		{
			rotation_ += D3DXToRadian(5.0f);
		}
		else if (rotation_ > D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(0.0f))
		{
			rotation_ -= D3DXToRadian(5.0f);
		}

		move_ = position_ - CCamera::GetEye();
		D3DXVec3Normalize(&move_, &move_);
		D3DXMATRIX moverot;
		D3DXMatrixRotationAxis(&moverot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180.0f));
		D3DXVec3TransformNormal(&move_, &move_, &moverot);
	}

	if (keyboard_->GetKeyPress(DIK_A))
	{	
		if (OldAxisX_)
		{
			rotation_ = D3DXToRadian(90.0f);
			OldAxisX_ = false;
		}
		if (rotation_ <= D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(90.0f))
		{
			rotation_ += D3DXToRadian(5.0f);
		}
		else if (rotation_ > D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(90.0f))
		{
			rotation_ -= D3DXToRadian(5.0f);
		}
		move_ = position_ - CCamera::GetEye();
		D3DXVec3Normalize(&move_, &move_);
		D3DXMATRIX moverot;
		D3DXMatrixRotationAxis(&moverot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-90.0f));
		D3DXVec3TransformNormal(&move_, &move_, &moverot);
	}
	if (keyboard_->GetKeyPress(DIK_D))
	{
		OldAxisX_ = true;
		if (OldAxisZ_)
		{
			rotation_ = D3DXToRadian(360.0f);
			OldAxisZ_ = false;
		}
		if (rotation_ >= D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(270.0f))
		{
			rotation_ -= D3DXToRadian(5.0f);
		}
		else if (rotation_ < D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(270.0f))
		{
			rotation_ += D3DXToRadian(5.0f);
		} 
		move_ = position_ - CCamera::GetEye();
		D3DXVec3Normalize(&move_, &move_);
		D3DXMATRIX moverot;
		D3DXMatrixRotationAxis(&moverot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(90.0f));
		D3DXVec3TransformNormal(&move_, &move_, &moverot);
	}

	if (rotation_ > D3DXToRadian(360.0f))
	{
		rotation_ -= D3DXToRadian(360.0f);
	}
	else if (rotation_ < -D3DXToRadian(360.0))
	{
		rotation_ += D3DXToRadian(360.0f);
	}
	position_ += move_ * 1.2f;
	D3DXMatrixRotationY(&_mtx_rotation, rotation_);
	D3DXMatrixTranslation(&_mtx_position, position_.x, position_.y, position_.z);
}