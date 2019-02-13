#include "ChutorialPlayer.h"
#include "../../../SceneManager/InheritanceNode/SceneChutorial.h"
#include "../MeshFiled.h"
#include "../../../Renderer/GameManager.h"
#include "../Camera.h"
#include "../MagicObject/MagicObject.h"
#include "../BossMonster/ChutorialBoss.h"
#include "../../Polygon2D.h"
#include "../Player/PlayerItem/PlayerWeapon.h"
#include "../Player/PlayerItem/PlayerShiled.h"
ChutorialPlayer::ChutorialPlayer()
	: GameObjectManager(0)
	, keyframe_(0)
	, sleeptime_ (0)
	, counttime_ (0)
	, diffencetime_ (0)
	, ActionUseFlag_(false)
	, runflag_(true)
{
}

ChutorialPlayer::~ChutorialPlayer()
{
}

void ChutorialPlayer::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Player.x");
	skinmesh_->SetAnimSpeed(2.0f);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
	D3DXMatrixScaling(&matrix_.scale, 30.0f, 30.0f, 30.0f);
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	position_ = D3DXVECTOR3(0.0f, 0.0f, -500.0f);
	upvec_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rightvec_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frontvec_ = CCamera::GetAt() - CCamera::GetEye();
	frontvec_.y = 0.0f;
	movespeed_ = 1.0f;
	D3DXVec3Normalize(&frontvec_, &frontvec_);
	animpattern_ = STATE;
	attackpattern_ = ACTIONPATTERN::STATE;
	rollflag_ = false;
}

void ChutorialPlayer::Update()
{
	//keyboard_ = GameManager::GetKeyboard();
	gamepad_ = GameManager::GetGamePad();

	position_.y = SceneChutorial::GetMeshFiled()->GetHeight(position_);
	
	skinmesh_->SetAnimSpeed(2.0f);
	Move();
	Attack();
	Magic();
	Diffence();

	skinmesh_->Update(matrix_.world);
	D3DXMATRIX mtxSword, mtxShiled;
	mtxSword = skinmesh_->GetBoneMatrix("Bip001_001_Bip001_R_Hand");
	mtxShiled = skinmesh_->GetBoneMatrix("Bip001_001_Bip001_L_Hand");
	SceneChutorial::GetSwordModel()->SetTargetBone(mtxSword);
	SceneChutorial::GetShiledModel()->SetTargetBone(mtxShiled);
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	keyframe_++;
}

void ChutorialPlayer::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	//裏面カリング(ポリゴンの裏面を描画しない)
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// フィルタ設定
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//ライトを無効にする
	device->LightEnable(0, true);
	// ライトの計算処理をしない
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//マテリアルの設定
	device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	skinmesh_->Draw(device);
}

void ChutorialPlayer::Uninit()
{
	skinmesh_->Release();
	delete skinmesh_;
	skinmesh_ = nullptr;
}

ChutorialPlayer * ChutorialPlayer::Create()
{
	ChutorialPlayer* ChutoPlayer_ = new ChutorialPlayer();
	ChutoPlayer_->Init();
	return ChutoPlayer_;
}

D3DXVECTOR3 ChutorialPlayer::GetPosition()
{
	return position_;
}

void ChutorialPlayer::Move()
{
	float x = 0, z = 0;
	if (gamepad_->GetState()._left_thumbstick.x > 0.25f)
	{
		x = gamepad_->GetState()._left_thumbstick.x;
	}
	else if(gamepad_->GetState()._left_thumbstick.x < -0.25f)
	{
		x = gamepad_->GetState()._left_thumbstick.x;
	}
	if (gamepad_->GetState()._left_thumbstick.y > 0.25f)
	{
		z = gamepad_->GetState()._left_thumbstick.y;
	}
	else if (gamepad_->GetState()._left_thumbstick.y < -0.25f)
	{
		z = gamepad_->GetState()._left_thumbstick.y;
	}
	//int x = -keyboard_->GetKeyPress(DIK_A) + keyboard_->GetKeyPress(DIK_D);
	//int z = -keyboard_->GetKeyPress(DIK_S) + keyboard_->GetKeyPress(DIK_W);

	move_ = D3DXVECTOR3((float)x, 0.0f, (float)z);
	D3DXVECTOR3 rotationalposition = D3DXVECTOR3((float)x, 0.0f, (float)z);
	frontvec_ = (position_)-GameManager::GetCamera()->GetEye();
	D3DXVec3Normalize(&frontvec_, &frontvec_);
	D3DXVec3Cross(&rightvec_, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &frontvec_);
	D3DXVec3Normalize(&rightvec_, &rightvec_);
	D3DXVec3Cross(&upvec_, &frontvec_, &rightvec_);

	D3DXMATRIX rotate;
	float moverotation = atan2(frontvec_.x, frontvec_.z) + D3DXToRadian(180.0f);
	D3DXMatrixRotationAxis(&rotate, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), moverotation);
	D3DXVec3TransformNormal(&move_, &move_, &rotate);

	SceneChutorial::GetLeftController()->SetControllPosX(gamepad_->GetState()._left_thumbstick.x);
	SceneChutorial::GetLeftController()->SetControllPosY(gamepad_->GetState()._left_thumbstick.y);
	if (!ActionUseFlag_)
	{
		if (x == 0 && z == 0)
		{
			if (animpattern_ != STATE)
			{
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(0.0f);
				sleeptime_ = 0;
				animpattern_ = STATE;
				movespeed_ = 0;
			}
		}
		if (gamepad_->GetState()._buttons[GamePad_Button_RIGHT_SHOULDER])
		{
			if (x != 0 || z != 0)
			{
				if (animpattern_ != ROLL)
				{
					if (runflag_)
					{
						runflag_ = false;
						skinmesh_->SetAnimSpeed(2.0f);
						skinmesh_->MyChangeAnim(9.63);
					}
					movespeed_ = RUNSPEED;
					animpattern_ = RUN;
				}
			}
		}
		else if (!gamepad_->GetState()._buttons[GamePad_Button_RIGHT_SHOULDER])
		{
			if (x != 0 || z != 0)
			{
				if (animpattern_ == RUN)
				{
					runflag_ = true;
					movespeed_ = WALKSPEED;
					skinmesh_->SetAnimSpeed(1.0f);
					skinmesh_->MyChangeAnim(6.6);
					sleeptime_ = 0;
					animpattern_ = WALK;
				}
				if (animpattern_ == STATE)
				{
					runflag_ = true;
					movespeed_ = WALKSPEED;
					skinmesh_->SetAnimSpeed(1.0f);
					skinmesh_->MyChangeAnim(6.6);
					sleeptime_ = 0;
					animpattern_ = WALK;
				}
			}
		}

		if (gamepad_->GetLeftControllerTrigger(LEFT))
		{
			if (animpattern_ == STATE && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ == WALK && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ != RUN && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);

				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ == RUN && rollflag_ == false)
			{
				movespeed_ = RUNSPEED;
				skinmesh_->SetAnimSpeed(2.0f);
				skinmesh_->MyChangeAnim(9.63);
				sleeptime_ = 0;
				animpattern_ = RUN;
			}
		}
		else if (gamepad_->GetLeftControllerTrigger(RIGHT))
		{
			if (animpattern_ == STATE && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ == WALK && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ != RUN && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);

				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ == RUN && rollflag_ == false)
			{
				movespeed_ = RUNSPEED;
				skinmesh_->SetAnimSpeed(2.0f);
				skinmesh_->MyChangeAnim(9.63);
				sleeptime_ = 0;
				animpattern_ = RUN;
			}
		}
		else if (gamepad_->GetLeftControllerTrigger(UP))
		{
			if (animpattern_ == STATE && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ == WALK && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ != RUN && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);

				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ == RUN && rollflag_ == false)
			{
				movespeed_ = RUNSPEED;
				skinmesh_->SetAnimSpeed(2.0f);
				skinmesh_->MyChangeAnim(9.63);
				sleeptime_ = 0;
				animpattern_ = RUN;
			}
		}
		else if (gamepad_->GetLeftControllerTrigger(DOWN))
		{
			if (animpattern_ == STATE && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ == WALK && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ != RUN && rollflag_ == false)
			{
				movespeed_ = WALKSPEED;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
				animpattern_ = WALK;
			}
			if (animpattern_ == RUN && rollflag_ == false)
			{
				movespeed_ = RUNSPEED;
				skinmesh_->SetAnimSpeed(2.0f);
				skinmesh_->MyChangeAnim(9.63);
				sleeptime_ = 0;
				animpattern_ = RUN;
			}
		}

		if (keyframe_ > 100)
		{
			if (gamepad_->GetState()._buttons[GamePad_Button_A])
			{
				if (animpattern_ == RUN)
				{
					rollflag_ = true;
					movespeed_ = ROLLSPEED;
					skinmesh_->SetAnimSpeed(2.0f);
					skinmesh_->MyChangeAnim(8.0);
					sleeptime_ = 0;
					keyframe_ = 0;
					animpattern_ = ROLL;
				}
			}
		}
	}
	
	//else if (gamepad_->GetButtonTrigger(GamePad_Button_RIGHT_SHOULDER))
	//{
	//	if (animpattern_ != RUN)
	//	{
	//		movespeed_ = RUNSPEED;
	//		skinmesh_->SetAnimSpeed(2.0f);
	//		skinmesh_->MyChangeAnim(9.63);
	//		sleeptime_ = 0;
	//		animpattern_ = RUN;
	//	}
	//}
	//else if (gamepad_->GetButtonPress(GamePad_Button_RIGHT_SHOULDER))
	//{
	//	if (animpattern_ != ROLL)
	//	{
	//		movespeed_ = RUNSPEED;
	//		animpattern_ = RUN;
	//	}
	//}
	//else if (gamepad_->GetButtonRelease(GamePad_Button_RIGHT_SHOULDER))
	//{
	//	if (animpattern_ != WALK)
	//	{
	//		movespeed_ = WALKSPEED;
	//		skinmesh_->SetAnimSpeed(1.0f);
	//		skinmesh_->MyChangeAnim(6.6);
	//		sleeptime_ = 0;
	//		animpattern_ = WALK;
	//	}
	//}

	if (!ActionUseFlag_)
	{
		switch (animpattern_)
		{
		case STATE:
			if (sleeptime_ < 180)
			{
				sleeptime_++;
			}
			else
			{
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(0.0);
				sleeptime_ = 0;
			}
			break;
		case WALK:
			if (sleeptime_ < 55)
			{
				sleeptime_++;
			}
			else {
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(6.6);
				sleeptime_ = 0;
			}
			break;
		case RUN:
			if (sleeptime_ < 34)
			{
				sleeptime_++;
			}
			else {
				skinmesh_->SetAnimSpeed(2.0f);
				skinmesh_->MyChangeAnim(9.63);
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
				skinmesh_->SetAnimSpeed(2.0f);
				skinmesh_->MyChangeAnim(9.63);
				sleeptime_ = 0;
				animpattern_ = RUN;
			}
			break;
		}
	}
	
	if (!ActionUseFlag_)
	{
		position_ -= move_ * movespeed_;
	}

	//初期位置変えられる
	static float oldmodelrotation = D3DXToRadian(180.0f);
	float modelrotation = 0.0f;
	modelrotation = oldmodelrotation;

	if (!ActionUseFlag_)
	{
		if (x != 0 || z != 0)
		{
			modelrotation = atan2(frontvec_.x, frontvec_.z) + D3DXToRadian(180.0f) + atan2(rotationalposition.x, rotationalposition.z);
			oldmodelrotation = modelrotation;
		}
	}

	D3DXMATRIX mtx_rot;
	D3DXMATRIX mtx_pos;
	
	if (position_.y > 54.0f)
	{
		D3DXMatrixRotationY(&mtx_rot, modelrotation);
		D3DXMatrixTranslation(&mtx_pos, position_.x, position_.y, position_.z);
	}
	else
	{
		if (position_.x < 0.0f)
		{
			position_.x += RUNSPEED * 2;
		}
		else
		{
			position_.x -= RUNSPEED * 2;
		}
		if (position_.z < 0.0f)
		{
			position_.z += RUNSPEED * 2;
		}
		else
		{
			position_.z -= RUNSPEED * 2;
		}
		D3DXMatrixRotationY(&mtx_rot, modelrotation);
		D3DXMatrixTranslation(&mtx_pos, position_.x, position_.y, position_.z);
	}

	matrix_.position = mtx_pos;
	matrix_.rotation = mtx_rot;
}

void ChutorialPlayer::Attack()
{
	skinmesh_->SetAnimSpeed(2.0f);
	if (keyframe_ > 60)
	{
		if (gamepad_->GetButtonTrigger(GamePad_Button_B))
		{
			ActionUseFlag_ = true;
			skinmesh_->MyChangeAnim(10.8);
			animpattern_ = NORMALATTACK;
			counttime_ = 0;
			keyframe_ = 0;
		}
	}

	switch (animpattern_)
	{
	case NORMALATTACK:
		if (counttime_ < 60)
		{
			counttime_++;
		}
		else
		{
			if (gamepad_->GetState()._buttons[GamePad_Button_RIGHT_SHOULDER])
			{
				if (animpattern_ != ROLL)
				{
					if (runflag_)
					{
						runflag_ = false;
						skinmesh_->SetAnimSpeed(2.0f);
						skinmesh_->MyChangeAnim(9.63);
					}
					ActionUseFlag_ = false;
					movespeed_ = RUNSPEED;
					animpattern_ = RUN;
					counttime_ = 0;
				}
			}
			else
			{
				animpattern_ = STATE;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(0.0);
				counttime_ = 0;
				ActionUseFlag_ = false;
			}
		}
		break;
	default:
		break;
	}
}

void ChutorialPlayer::Magic()
{
	if (keyframe_ > 150)
	{
		if (gamepad_->GetButtonTrigger(GamePad_Button_X))
		{
			ActionUseFlag_ = true;
			SceneChutorial::GetPlayerMagicEfk()->SetPosition(position_);
			SceneChutorial::GetPlayerMagicEfk()->SetIsDrawing(true);
			SceneChutorial::GetPlayerMagicEfk()->SetFrameCount(1.0f);
			SceneChutorial::GetMagic()->StartMagic(SceneChutorial::GetChutorialBoss()->GetPosition(), position_);
			//MagicObject::StartMagic(SceneChutorial::GetChutorialBoss()->GetPosition(), position_);
			animpattern_ = MAGIC;
			skinmesh_->SetAnimSpeed(2.0f);
			skinmesh_->MyChangeAnim(24);
			keyframe_ = 0;
			magictime_ = 0;
		}
	}
	
	switch (animpattern_)
	{
	case MAGIC:
		if (magictime_ < 120)
		{
			if (magictime_ > 60)
			{
				SceneChutorial::GetPlayerMagicEfk()->SetIsDrawing(false);
			}
			magictime_++;
		}
		else
		{
			if (gamepad_->GetState()._buttons[GamePad_Button_RIGHT_SHOULDER])
			{
				if (animpattern_ != ROLL)
				{
					if (runflag_)
					{
						runflag_ = false;
						skinmesh_->SetAnimSpeed(2.0f);
						skinmesh_->MyChangeAnim(9.63);
					}
					ActionUseFlag_ = false;
					movespeed_ = RUNSPEED;
					animpattern_ = RUN;
					magictime_ = 0;
				}
			}
			else
			{
				ActionUseFlag_ = false;
				skinmesh_->SetAnimSpeed(1.0f);
				skinmesh_->MyChangeAnim(0.0f);
				animpattern_ = STATE;
				magictime_ = 0;
			}
		}
	default:
		break;
	}
}

void ChutorialPlayer::Diffence()
{
	if (gamepad_->GetButtonTrigger(GamePad_Button_Y))
	{
		diffencetime_ = 0;
		ActionUseFlag_ = true;
		animpattern_ = DSTART;
		skinmesh_->SetAnimSpeed(1.0f);
		skinmesh_->MyChangeAnim(18.7);
		keyframe_ = 0;
	}
	if (gamepad_->GetButtonRelease(GamePad_Button_Y))
	{
		diffencetime_ = 0;
		ActionUseFlag_ = false;
		skinmesh_->SetAnimSpeed(1.0f);
		skinmesh_->MyChangeAnim(0.0);
		keyframe_ = 0;
		animpattern_ = STATE;
	}

	switch (animpattern_)
	{
	case DSTART:
		if (diffencetime_ < 60)
		{
			diffencetime_++;
		}
		else
		{
			skinmesh_->SetAnimSpeed(1.0f);
			skinmesh_->MyChangeAnim(20.5);
			attackpattern_ = ACTIONPATTERN::DEND;
			diffencetime_ ++;
		}
		break;
	case DEFFENCE:
		skinmesh_->SetAnimSpeed(1.0f);
		skinmesh_->MyChangeAnim(20.5);
		diffencetime_ = 0;
		break;
	default:
		break;
	}
}
