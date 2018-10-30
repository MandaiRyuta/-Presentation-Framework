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

	int x = -keyboard_->GetKeyPress(DIK_A) + keyboard_->GetKeyPress(DIK_D);
	int z = -keyboard_->GetKeyPress(DIK_S) + keyboard_->GetKeyPress(DIK_W);

	move_ = D3DXVECTOR3((float)x, 0.0f, (float)z);
	D3DXVECTOR3 rotationalposition = D3DXVECTOR3((float)x, 0.0f, (float)z);
	frontvec_ = (position_)-CCamera::GetEye();
	D3DXVec3Normalize(&frontvec_, &frontvec_);
	D3DXVec3Cross(&rightvec_, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &frontvec_);
	D3DXVec3Normalize(&rightvec_, &rightvec_);
	D3DXVec3Cross(&upvec_, &frontvec_, &rightvec_);

	D3DXMATRIX setrot;
	float moverotation = atan2(frontvec_.x, frontvec_.z) + D3DXToRadian(180.0f);
	D3DXMatrixRotationAxis(&setrot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), moverotation);
	D3DXVec3TransformNormal(&move_, &move_, &setrot);
	static int counttime = 0;

	if (x == 0 && z == 0)
	{
		if (!movemode_)
		{
			_skinmesh->SetAnimTrack(0.15);
			movemode_ = true;
		}
		if (counttime <= 90)
		{
			counttime++;
		}
		else
		{
			movemode_ = false;
			_skinmesh->SetAnimSpeed(0.01f);
			counttime = 0;
		}
	}
	else
	{
		movemode_ = false;
		if (!keyboard_->GetKeyPress(DIK_LSHIFT))
		{
			if (counttime <= 50)
			{
				counttime++;
			}
			else
			{
				_skinmesh->SetAnimTrack(0);
				counttime = 0;
			}
		}
		if (keyboard_->GetKeyRelease(DIK_LSHIFT))
		{
			movespeed_ = 1.2f;
			_skinmesh->SetAnimTrack(0);
			counttime = 0;
		}
		if (keyboard_->GetKeyPress(DIK_LSHIFT))
		{
			movespeed_ = 2.0f;
			if (counttime <= 34)
			{
				counttime++;
			}
			else
			{
				_skinmesh->SetAnimTrack(0.008);
				counttime = 0;
			}
		}
	}


	position_ -= move_ * movespeed_;
	static float oldmodelrotation = 0.0f;
	float modelrotation = 0.0f;
	modelrotation = oldmodelrotation;
	if (x != 0 || z != 0)
	{
		modelrotation = atan2(frontvec_.x, frontvec_.z) + D3DXToRadian(180.0f) + atan2(rotationalposition.x, rotationalposition.z);
		oldmodelrotation = modelrotation;
	}

	D3DXMatrixRotationY(&_mtx_rotation, modelrotation);

	D3DXMatrixTranslation(&_mtx_position, position_.x, position_.y, position_.z);
}