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
	static int sleeptime = 0;
	if (x == 0 && z == 0)
	{
		sleeptime++;
		if (sleeptime >= 15)
		{
			_skinmesh->SetAnimSpeed(0.02f);
			_skinmesh->SetAnimTrack(0.15);
			AnimPattern_ = STATE;
		}
	}
	else
	{
		sleeptime = 0;
	}

	if (keyboard_->GetKeyTrigger(DIK_A))
	{
		AnimPattern_ = WALK;
		_skinmesh->SetAnimSpeed(0.015f);
	}
	else if (keyboard_->GetKeyTrigger(DIK_D))
	{
		AnimPattern_ = WALK;
		_skinmesh->SetAnimSpeed(0.015f);
	}
	else if (keyboard_->GetKeyTrigger(DIK_W))
	{
		AnimPattern_ = WALK;
		_skinmesh->SetAnimSpeed(0.015f);
	}
	else if (keyboard_->GetKeyTrigger(DIK_S))
	{
		AnimPattern_ = WALK;
		_skinmesh->SetAnimSpeed(0.015f);
	}

	if (keyboard_->GetKeyPress(DIK_LSHIFT))
	{
		_skinmesh->SetAnimSpeed(0.02f);
		AnimPattern_ = RUN;
	}
	if (keyboard_->GetKeyRelease(DIK_LSHIFT))
	{
		_skinmesh->SetAnimSpeed(0.015f);
		AnimPattern_ = WALK;
	}

	switch (AnimPattern_)
	{
	case STATE:
		if (counttime <= 30)
		{
			counttime++;
		}
		else
		{
			_skinmesh->SetAnimTrack(0.15);
			counttime = 0;
		}
		break;
	case WALK:
		movespeed_ = 1.2f;
		if (counttime <= 40)
		{
			counttime++;
		}
		else
		{
			_skinmesh->SetAnimTrack(0);
			counttime = 0;
		}
		break;
	case RUN:
		movespeed_ = 2.0f;
		if (counttime <= 20)
		{
			counttime++;
		}
		else
		{
			_skinmesh->SetAnimTrack(0.008);
			counttime = 0;
		}
		break;
	default:
		break;
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