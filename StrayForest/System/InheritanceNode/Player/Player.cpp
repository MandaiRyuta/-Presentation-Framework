#include "Player.h"
#include "../../../main.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Camera.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../MeshFiled.h"
#include "../../../InputManager/XBoxController.h"
#include "../../../Renderer/GameManager.h"
#include "PlayerMove\PlayerMoveManager.h"
#include "PlayerAttack\PlayerAttackManager.h"
#include "PlayerBuffState\PlayerBuffStateManager.h"
#include "PlayerDiffence\PlayerDiffenceManager.h"
#include "PlayerMagic\PlayerMagicManager.h"
#include "PlayerBuffState\PlayerBuffStateManager.h"
#include "PlayerMove\PlayerMove.h"
#include "PlayerItem\PlayerShiled.h"
#include "PlayerItem\PlayerWeapon.h"
#include "PlayerMagic\PlayerMagic.h"
#include "PlayerDiffence\PlayerDiffence.h"
#include "PlayerBuffState\PlayerBuff.h"
#include "PlayerAttack\PlayerNomalAttack.h"
#include "../MyEffekseer/MyEffekseer.h"
#include "PlayerState\PlayerStateManager.h"
#include "PlayerState\PlayerState.h"
#include "../../colision/SphereColision.h"
#include "../BossMonster/BossMonster.h"
#include "../../Polygon2D.h"

D3DXMATRIX Player::world_;
D3DXMATRIX Player::rot_;
D3DXMATRIX Player::pos_;
D3DXMATRIX Player::body_;
SphereColision* Player::AttackHitColision_ = nullptr;

Player::Player(float max_health, float max_mana, float health, float mana)
	: GameObjectManager(0)
	, movemanager_(new PlayerMove)
	, magicmanager_(new PlayerMagic(this))
	, attackmanager_(new PlayerNomalAttack(this))
	, diffencemanager_(new PlayerDiffence(this))
	, buffmanager_(new PlayerBuff(this))
	, statusmanager_(new PlayerState(this))
	, playeraction_(STATE)
	, StateMode_(false)
	, spherecolision_(new SphereColision)
	, Max_Life_(max_health)
	, Max_Mana_(max_mana)
	, Life_(health)
	, Mana_(mana)
	, Diffence_(false)
	, oldPosition_(D3DXVECTOR3(0.0f, 0.0f, -500.0f))
	, keyframe_(400)
	, cameraflag_(false)
	, oldposframetime_(0)
	, movecolisioncheck_(false)
	, rotate_(0.0f)
	, ActionUseFlag_(false)
	, MagicUseFlag_(false)
{
}
void Player::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Player.x");
	scale_ = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
	D3DXMatrixIdentity(&rot_);
	D3DXMatrixIdentity(&pos_);
	D3DXMatrixIdentity(&world_);
	position_ = D3DXVECTOR3(0.0f, 0.0f, -500.0f);
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);
	
	moveinfo_.colision01.r = 35.0f;
	moveinfo_.colision02.r = 28.0f;
	moveinfo_.center_to_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	moveinfo_.hit_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	moveinfo_.hit_vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	moveinfo_.two_radius = 0.0f;
	knockback_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Player::Update()
{
	//ImGui::GetPositionInfomation("PLAYER_POSITION", position_);
	gamepad_ = GameManager::GetGamePad();
	//keyboard_ = GameManager::GetKeyboard();
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);
	D3DXVECTOR3 bossposition = SceneGame::GetBossMonster()->GetPosition();

	moveinfo_.colision01.modelpos = D3DXVECTOR3(bossposition.x, bossposition.y, bossposition.z);
	moveinfo_.colision02.modelpos = D3DXVECTOR3(position_.x, position_.y, position_.z);
	movecolisioncheck_ = spherecolision_->Collision_detection_of_Sphere_and_Sphere(moveinfo_);

	if (!cameraflag_)
	{
		skinmesh_->SetAnimSpeed(0.0f);
		movemanager_->Update(this);
	}
	else if (cameraflag_)
	{
		skinmesh_->SetAnimSpeed(2.0f);
		
		movemanager_->Update(this);
		magicmanager_->Update(this);
		diffencemanager_->Update(this);
		buffmanager_->Update(this);
		attackmanager_->Update(this);
		statusmanager_->Update(this);
	}

	if (position_.y > 54.0f)
	{
		D3DXMatrixRotationY(&matrix_.rotation, rotate_);
		D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);
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
	}

	pos_ = matrix_.position;
	rot_ = matrix_.rotation;
	world_ = matrix_.world;
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	skinmesh_->Update(matrix_.world);	
	D3DXMATRIX mtxSword, mtxShiled;
	mtxSword = skinmesh_->GetBoneMatrix("Bip001_001_Bip001_R_Hand");
	mtxShiled = skinmesh_->GetBoneMatrix("Bip001_001_Bip001_L_Hand");
	body_ = skinmesh_->GetBoneMatrix("Bip001_001_Bip001_Head");
	SceneGame::GetPlayerShiled()->SetTargetBone(mtxShiled);
	SceneGame::GetPlayerSword()->SetTargetBone(mtxSword);

	keyframe_++;
	oldposframetime_++;
}

void Player::Draw()
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

	//item_->ShiledDraw(device,mtxShiled);
	//item_->SwordDraw(device,mtxSword);
	skinmesh_->Draw(device);
}

void Player::Uninit()
{
	if (skinmesh_ != nullptr)
	{
		skinmesh_->Release();
		delete skinmesh_;
	}
	//item_->Uninit();
	if (spherecolision_ != nullptr)
	{
		delete spherecolision_;
	}
	//delete item_;
	if (statusmanager_ != nullptr)
	{
		delete statusmanager_;
	}
	if (movemanager_ != nullptr)
	{
		delete movemanager_;
	}
	if (attackmanager_ != nullptr)
	{
		delete attackmanager_;
	}
	if (buffmanager_ != nullptr)
	{
		delete buffmanager_;
	}
	if (diffencemanager_ != nullptr)
	{
		delete diffencemanager_;
	}
	if (magicmanager_ != nullptr)
	{
		delete magicmanager_;
	}
}

void Player::Damage(float _damage, D3DXVECTOR3 knockback)
{
	//knockbackflag_ = true;
	knockback_ = knockback;
	Life_ -= _damage;
}

void Player::UseMana(float _mana)
{
	Mana_ -= _mana;
}

void Player::Heal(double _animtrack, float _speed, int _amount)
{
	Life_ += _amount;
	
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::Attack(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::Skill(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::Magic(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::Buff(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::DeBuff(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

Player * Player::Create(float max_health, float max_mana, float health, float mana)
{
	Player* CreatePlayer = new Player(max_health, max_mana, health, mana);
	CreatePlayer->Init();
	return CreatePlayer;
}

void Player::ChangeMovePattern(PlayerMoveManager * _move)
{
	delete movemanager_;
	movemanager_ = _move;
}

void Player::ChangeAttackPattern(PlayerAttackManager* _attack)
{
	delete attackmanager_;
	attackmanager_ = _attack;
}

void Player::ChangeMagicPattern(PlayerMagicManager* _magic)
{
	delete magicmanager_;
	magicmanager_ = _magic;
}

void Player::ChangeBuffMode(PlayerBuffStateManager * _buff)
{
	delete buffmanager_;
	buffmanager_ = _buff;
}

void Player::ChangeDiffencePattern(PlayerDiffenceManager * _diffence)
{
	delete diffencemanager_;
	diffencemanager_ = _diffence;
}

bool Player::GetSphereColisionFlag()
{
	return movecolisioncheck_;
}

Entity::SphereColision Player::GetSphereColisionInfo()
{
	return moveinfo_;
}

CSkinMesh * Player::GetSkinMesh()
{
	return skinmesh_;
}

GamePadXbox * Player::GetGamePad()
{
	return gamepad_;
}

void Player::SetPlayerPosition(D3DXVECTOR3 _pos)
{
	position_ = _pos;
}

void Player::SetPlayerMatrix(D3DXMATRIX _world)
{
	matrix_.world = _world;
}

void Player::SetPlayerPosMatrix(D3DXMATRIX _pos)
{
	matrix_.position = _pos;
}

void Player::SetPlayerRotMatrix(D3DXMATRIX _rot)
{
	matrix_.rotation = _rot;
}

void Player::SetActionPattern(ACTIONPATTERN _action)
{
	playeraction_ = _action;
}

void Player::SetStateMode(bool _StateMode)
{
	StateMode_ = _StateMode;
}

void Player::SetDiffenceMode(bool _diffence)
{
	Diffence_ = _diffence;
}

void Player::SetOldPosition(D3DXVECTOR3 _pos)
{
	oldPosition_ = _pos;
}

void Player::SetKeyframe(int _keyframe)
{
	keyframe_ = _keyframe;
}

void Player::SetCameraMove(bool _cameraflag)
{
	cameraflag_ = _cameraflag;
}

void Player::SetOldPosFrame(int _oldposframe)
{
	oldposframetime_ = _oldposframe;
}

void Player::SetRotation(float _rotation)
{
	rotate_ = _rotation;
}

void Player::SetActionUseFlag(bool _actionusecheck)
{
	ActionUseFlag_ = _actionusecheck;
}

bool Player::GetCameraMove()
{
	return cameraflag_;
}

void Player::addLife(float _Life)
{
	if (Life_ < Max_Life_)
	{
		Life_ += _Life;
	}
}

void Player::addmana(float _Mana)
{
	if (Mana_ < Max_Mana_)
	{
		Mana_ += _Mana;
	}
}

int Player::GetKeyframe()
{
	return keyframe_;
}

int Player::GetOldPosFrame()
{
	return oldposframetime_;
}

bool Player::GetStateMode()
{
	return StateMode_;
}

bool Player::GetDiffenceMode()
{
	return Diffence_;
}

float Player::GetRotation()
{
	return rotate_;
}

D3DXVECTOR3 Player::GetOldPosition()
{
	return oldPosition_;
}

ACTIONPATTERN& Player::GetActionPattern()
{
	return playeraction_;
}

D3DXVECTOR3 Player::GetPlayerPosition()
{
	return position_;
}

bool Player::GetColisionFlag()
{
	return movecolisioncheck_;
}

bool Player::GetActionUseFlag()
{
	return ActionUseFlag_;
}

D3DXVECTOR3 & Player::GetPosition()
{
	return position_;
}

D3DXVECTOR3 Player::Getknokback()
{
	D3DXVec3Normalize(&knockback_, &knockback_);
	return knockback_;
}

Entity::SphereColision& Player::GetColisioninfo()
{
	return moveinfo_;
}

D3DXMATRIX & Player::GetPlayerMatrix()
{
	return world_;
}

D3DXMATRIX & Player::GetPlayerPosMatrix()
{
	return pos_;
}

D3DXMATRIX & Player::GetPlayerRotMatrix()
{
	return rot_;
}

D3DXMATRIX & Player::GetPlayerBodyMatrix()
{
	return body_;
}

SphereColision * Player::AttackColision()
{
	return AttackHitColision_;
}
