#include "PlayerMove.h"
#include "../Player.h"
#include "../../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MeshFiled.h"
#include "../../../../InputManager/input.h"
#include "../../../../Renderer/GameManager.h"
#include "../../Camera.h"
#include "../../../Sound.h"
PlayerMove::PlayerMove()
{
	position_ = D3DXVECTOR3(0.0f, 0.0f, -500.0f);
	upvec_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rightvec_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frontvec_ = CCamera::GetAt() - CCamera::GetEye();
	frontvec_.y = 0.0f;
	movespeed_ = 1.0f;
	D3DXVec3Normalize(&frontvec_, &frontvec_);
	AnimPattern_ = STATE;
	counttime_ = 0;
	sleeptime_ = 0;
	rollflag_ = false;
	runflag_ = true;
		//初期位置変えられる
	oldmodelrotation_ = D3DXToRadian(180.0f);
}

PlayerMove::~PlayerMove()
{
}

void PlayerMove::Update(Player * _player)
{
	stickx_ = 0.0;
	sticky_ = 0.0;

	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);

	if (_player->GetCameraMove())
	{
		if (_player->GetGamePad()->GetState()._left_thumbstick.x > 0.05)
		{
			stickx_ = _player->GetGamePad()->GetState()._left_thumbstick.x;
		}
		if (_player->GetGamePad()->GetState()._left_thumbstick.x < -0.05)
		{
			stickx_ = _player->GetGamePad()->GetState()._left_thumbstick.x;
		}

		if (_player->GetGamePad()->GetState()._left_thumbstick.y > 0.05)
		{
			sticky_ = _player->GetGamePad()->GetState()._left_thumbstick.y;
		}
		if (_player->GetGamePad()->GetState()._left_thumbstick.y < -0.05)
		{
			sticky_ = _player->GetGamePad()->GetState()._left_thumbstick.y;
		}
	}

	//int x = -_player->GetKeyboard()->GetKeyPress(DIK_A) + _player->GetKeyboard()->GetKeyPress(DIK_D);
	//int z = -_player->GetKeyboard()->GetKeyPress(DIK_S) + _player->GetKeyboard()->GetKeyPress(DIK_W);

	move_ = D3DXVECTOR3((float)stickx_, 0.0f, (float)sticky_);
	D3DXVECTOR3 rotationalposition = D3DXVECTOR3((float)stickx_, 0.0f, (float)sticky_);
	frontvec_ = (_player->GetPlayerPosition()) - GameManager::GetCamera()->GetEye();
	D3DXVec3Normalize(&frontvec_, &frontvec_);
	D3DXVec3Cross(&rightvec_, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &frontvec_);
	D3DXVec3Normalize(&rightvec_, &rightvec_);
	D3DXVec3Cross(&upvec_, &frontvec_, &rightvec_);

	D3DXMATRIX setrot;
	float moverotation = atan2(frontvec_.x, frontvec_.z) + D3DXToRadian(180.0f);
	D3DXMatrixRotationAxis(&setrot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), moverotation);
	D3DXVec3TransformNormal(&move_, &move_, &setrot);

	if (_player->GetCameraMove())
	{
		if (!_player->GetActionUseFlag())
		{
			if (stickx_ == 0.0000f && sticky_ == 0.0000f)
			{
				if (AnimPattern_ != STATE)
				{
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(0.0);
					sleeptime_ = 0;
					AnimPattern_ = STATE;
					//movespeed_ = 0.0f;
				}
			}
		
			if (_player->GetGamePad()->GetState()._buttons[GamePad_Button_RIGHT_SHOULDER])
			{
				if (stickx_ != 0 || sticky_ != 0)
				{
					if (AnimPattern_ != ROLL)
					{
						if (runflag_)
						{
							_player->GetSkinMesh()->SetAnimSpeed(2.0f);
							_player->GetSkinMesh()->MyChangeAnim(9.63);
							runflag_ = false;
						}
						movespeed_ = RUNSPEED;
						AnimPattern_ = RUN;
					}
				}
			}
			else if (!_player->GetGamePad()->GetState()._buttons[GamePad_Button_RIGHT_SHOULDER])
			{
				if (stickx_ != 0 || sticky_ != 0)
				{
					if (AnimPattern_ == RUN)
					{
						runflag_ = true;
						movespeed_ = WALKSPEED;
						_player->GetSkinMesh()->SetAnimSpeed(1.0f);
						_player->GetSkinMesh()->MyChangeAnim(6.6);
						sleeptime_ = 0;
						AnimPattern_ = WALK;
					}
					if (AnimPattern_ == STATE)
					{
						runflag_ = true;
						movespeed_ = WALKSPEED;
						_player->GetSkinMesh()->SetAnimSpeed(1.0f);
						_player->GetSkinMesh()->MyChangeAnim(6.6);
						sleeptime_ = 0;
						AnimPattern_ = WALK;
					}
				}
			}

			if (_player->GetGamePad()->GetLeftControllerTrigger(LEFT))
			{
				if (AnimPattern_ == STATE && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ == WALK && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ != RUN && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ == RUN && rollflag_ == false)
				{
					movespeed_ = RUNSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(2.0f);
					_player->GetSkinMesh()->MyChangeAnim(9.63);
					sleeptime_ = 0;
					AnimPattern_ = RUN;
				}
			}
			else if (_player->GetGamePad()->GetLeftControllerTrigger(RIGHT))
			{
				if (AnimPattern_ == STATE && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ == WALK && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ != RUN && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ == RUN && rollflag_ == false)
				{
					movespeed_ = RUNSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(2.0f);
					_player->GetSkinMesh()->MyChangeAnim(9.63);
					sleeptime_ = 0;
					AnimPattern_ = RUN;
				}
			}
			else if (_player->GetGamePad()->GetLeftControllerTrigger(UP))
			{
				if (AnimPattern_ == STATE && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ == WALK && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ != RUN && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ == RUN && rollflag_ == false)
				{
					movespeed_ = RUNSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(2.0f);
					_player->GetSkinMesh()->MyChangeAnim(9.63);
					sleeptime_ = 0;
					AnimPattern_ = RUN;
				}
			}
			else if (_player->GetGamePad()->GetLeftControllerTrigger(DOWN))
			{
				if (AnimPattern_ == STATE && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ == WALK && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);
					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ != RUN && rollflag_ == false)
				{
					movespeed_ = WALKSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(1.0f);
					_player->GetSkinMesh()->MyChangeAnim(6.6);

					sleeptime_ = 0;
					AnimPattern_ = WALK;
				}
				if (AnimPattern_ == RUN && rollflag_ == false)
				{
					movespeed_ = RUNSPEED;
					_player->GetSkinMesh()->SetAnimSpeed(2.0f);
					_player->GetSkinMesh()->MyChangeAnim(9.63);
					sleeptime_ = 0;
					AnimPattern_ = RUN;
				}
			}

			if (_player->GetKeyframe() > 100)
			{
				if (_player->GetGamePad()->GetState()._buttons[GamePad_Button_A])
				{
					if (AnimPattern_ == RUN)
					{
						rollflag_ = true;
						movespeed_ = ROLLSPEED;
						_player->GetSkinMesh()->SetAnimSpeed(2.0f);
						_player->GetSkinMesh()->MyChangeAnim(8.0);
						sleeptime_ = 0;
						_player->SetKeyframe(0);
						AnimPattern_ = ROLL;
					}
				}
			}
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
	if (!_player->GetActionUseFlag())
	{
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
				rollflag_ = false;
				_player->GetSkinMesh()->SetAnimSpeed(2.0f);
				_player->GetSkinMesh()->MyChangeAnim(9.63);
				sleeptime_ = 0;
				AnimPattern_ = RUN;
			}
			break;
		}
	}

	if (SceneGame::GetBossMonster()->GetMagicPositionFlag())
	{
		_player->SetOldPosition(_player->GetPosition());
		SceneGame::GetBossMonster()->SetMagicPositionFlag(false);
		//_player->SetOldPosFrame(0);
	}

	//移動させてから最終的にめり込み量を計算させる。
	if (!_player->GetActionUseFlag())
	{
		_player->GetPosition() -= move_ * movespeed_;
	}

	if (_player->GetColisionFlag())
	{
		_player->GetPosition() += _player->GetColisioninfo().hit_vector;
	}

	float modelrotation = 0.0f;
	modelrotation = oldmodelrotation_;
	
	if (!_player->GetActionUseFlag())
	{
		if (stickx_ != 0 || sticky_ != 0)
		{
			modelrotation = atan2(frontvec_.x, frontvec_.z) + D3DXToRadian(180.0f) + atan2(rotationalposition.x, rotationalposition.z);
			oldmodelrotation_ = modelrotation;
		}
	}

	_player->GetPosition() += _player->Getknokback() * 10.0f;

	_player->SetRotation(modelrotation);
}
