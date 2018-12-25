#include "PlayerMove.h"
#include "../Player.h"
#include "../../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MeshFiled.h"
#include "../../../../InputManager/input.h"
#include "../../../../Renderer/GameManager.h"

constexpr float WALKSPEED = 0.5f;
constexpr float RUNSPEED = 2.5f;
PlayerMove::PlayerMove()
{
	position_ = D3DXVECTOR3(0.0f, 0.0f, -500.0f);
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

PlayerMove::~PlayerMove()
{
}

void PlayerMove::Update(Player * _player)
{
	position_ = CCamera::GetAt();
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);

	int x = -_player->GetKeyboard()->GetKeyPress(DIK_A) + _player->GetKeyboard()->GetKeyPress(DIK_D);
	int z = -_player->GetKeyboard()->GetKeyPress(DIK_S) + _player->GetKeyboard()->GetKeyPress(DIK_W);
	//movecolisioninfo_.colision01.modelpos = position_;
	//movecolisioninfo_.colision02.modelpos = D3DXVECTOR3(::GetPlayerPosMatrix()._41, Player::GetPlayerPosMatrix()._42, Player::GetPlayerPosMatrix()._43);
	//bool colisioncheck = movecolision_->Collision_detection_of_Sphere_and_Sphere(movecolisioninfo_);
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

	if (x == 0 && z == 0)
	{
		if (AnimPattern_ != STATE)
		{
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			sleeptime_ = 0;
			AnimPattern_ = STATE;
		}
	}
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_A))
	{
		if (AnimPattern_ == WALK)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
		if (AnimPattern_ != RUN)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
		else if (AnimPattern_ == RUN)
		{
			movespeed_ = RUNSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(2.0f);
			_player->GetSkinMesh()->MyChangeAnim(9.63);
			sleeptime_ = 0;
			AnimPattern_ = RUN;
		}
	}
	else if (_player->GetKeyboard()->GetKeyTrigger(DIK_D))
	{
		if (AnimPattern_ == WALK)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
		if (AnimPattern_ != RUN)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
		else if (AnimPattern_ == RUN)
		{
			movespeed_ = RUNSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(2.0f);
			_player->GetSkinMesh()->MyChangeAnim(9.63);
			sleeptime_ = 0;
			AnimPattern_ = RUN;
		}
	}
	else if (_player->GetKeyboard()->GetKeyTrigger(DIK_W))
	{	
		if (AnimPattern_ == WALK)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
		if (AnimPattern_ != RUN)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
		else if (AnimPattern_ == RUN)
		{
			movespeed_ = RUNSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(2.0f);
			_player->GetSkinMesh()->MyChangeAnim(9.63);
			sleeptime_ = 0;
			AnimPattern_ = RUN;
		}
	}
	else if (_player->GetKeyboard()->GetKeyTrigger(DIK_S))
	{
		if (AnimPattern_ == WALK)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
		if (AnimPattern_ != RUN)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);

			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
		else if (AnimPattern_ == RUN)
		{
			movespeed_ = RUNSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(2.0f);
			_player->GetSkinMesh()->MyChangeAnim(9.63);
			sleeptime_ = 0;
			AnimPattern_ = RUN;
		}
	}
	else if (_player->GetKeyboard()->GetKeyTrigger(DIK_LSHIFT))
	{	
		if (AnimPattern_ != RUN)
		{
			movespeed_ = RUNSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(2.0f);
			_player->GetSkinMesh()->MyChangeAnim(9.63);
			sleeptime_ = 0;
			AnimPattern_ = RUN;
		}
	}
	else if (_player->GetKeyboard()->GetKeyPress(DIK_LSHIFT))
	{
		movespeed_ = RUNSPEED;
		AnimPattern_ = RUN;
	}
	else if (_player->GetKeyboard()->GetKeyRelease(DIK_LSHIFT))
	{
		if (AnimPattern_ != WALK)
		{
			movespeed_ = WALKSPEED;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
			AnimPattern_ = WALK;
		}
	}
	
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_SPACE))
	{
		if (AnimPattern_ == RUN)
		{
			_player->GetSkinMesh()->SetAnimSpeed(2.0f);
			_player->GetSkinMesh()->MyChangeAnim(8.0);
			sleeptime_ = 0;
			AnimPattern_ = ROLL;
		}
	}

	//if (_player->GetKeyboard()->GetKeyPress(DIK_LSHIFT))
	//{
	//	_player->GetSkinMesh()->MyChangeAnim(0.02f);
	//	AnimPattern_ = RUN;
	//}
	//if (_player->GetKeyboard()->GetKeyRelease(DIK_LSHIFT))
	//{
	//	_player->GetSkinMesh()->SetAnimSpeed(0.015f);
	//	AnimPattern_ = WALK;
	//}

	switch (AnimPattern_)
	{
	case STATE:
		if (sleeptime_ < 180)
		{
			sleeptime_++;
		}
		else
		{
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			sleeptime_ = 0;
		}
		break;
	case WALK:
		if (sleeptime_ < 55)
		{
			sleeptime_++;
		}
		else {
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(6.6);
			sleeptime_ = 0;
		}
		break;
	case RUN:
		if (sleeptime_ < 34)
		{
			sleeptime_++;
		}
		else {
			_player->GetSkinMesh()->SetAnimSpeed(2.0f);
			_player->GetSkinMesh()->MyChangeAnim(9.63);
			sleeptime_ = 0;
		}
		break;
	case ROLL:
		if (sleeptime_ < 58)
		{
			sleeptime_++;
		}
		else {
			_player->GetSkinMesh()->SetAnimSpeed(2.0f);
			_player->GetSkinMesh()->MyChangeAnim(9.63);
			sleeptime_ = 0;
			AnimPattern_ = RUN;
		}
		break;
	}

	position_ -= move_ * movespeed_;
	//‰ŠúˆÊ’u•Ï‚¦‚ç‚ê‚é
	static float oldmodelrotation = D3DXToRadian(180.0f);
	float modelrotation = 0.0f;
	modelrotation = oldmodelrotation;

	if (x != 0 || z != 0)
	{
		modelrotation = atan2(frontvec_.x, frontvec_.z) + D3DXToRadian(180.0f) + atan2(rotationalposition.x, rotationalposition.z);
		oldmodelrotation = modelrotation;
	}

	D3DXMATRIX mtx_rot;
	D3DXMATRIX mtx_pos;
	D3DXMatrixRotationY(&mtx_rot, modelrotation);
	D3DXMatrixTranslation(&mtx_pos, position_.x, position_.y, position_.z);
	_player->SetPlayerPosMatrix(mtx_pos);
	_player->SetPlayerRotMatrix(mtx_rot);
}
