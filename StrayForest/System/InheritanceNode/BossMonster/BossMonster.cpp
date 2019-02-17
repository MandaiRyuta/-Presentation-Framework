#include "BossMonster.h"
#include "BossMonsterPatterns\BossMonsterPatternA.h"
#include "../MeshFiled.h"
#include "BossMonsterAttack\BossMonsterAttackPattern.h"
#include "BossMonsterMagic\BossMonsterMagicPattern.h"
#include "BossMonsterPatterns\BossMonsterPattern.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "BossMonsterAttack\BossMonsterAttackPatternA.h"
#include "../Player/Player.h"
#include "BossStatus\BossStatusManager.h"
#include "BossStatus\BossStatus.h"
#include "BossMonsterMagic\BossMonsterMagicPatternA.h"

D3DXVECTOR3 BossMonster::GetPos_;
D3DXMATRIX BossMonster::GetRotation_;

BossMonster::BossMonster(float _Max_Life, float _Max_Mana)
	: GameObjectManager(0)
	, bosspattern_(new BossMonsterPatternNone)
	, magic_(new BossMonsterMagicPatternA)
	, attack_(new BossMonsterAttackPatternA)
	, max_life_(_Max_Life)
	, life_(_Max_Life)
	, max_mana_(_Max_Mana)
	, mana_(_Max_Mana)
	, movecolision_(new SphereColision)
	, statusmanager_(new BossStatus)
	, movecheckcolision_(false)
	, movestatecheck_(false)
	, cameraflag_(false)
	, camerastartcount_(0)
	, StateNum_(0)
	, nowattack_(false)
	, magicsetflag_(false)
	, attackframe_(145)
{
}

void BossMonster::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Boss.x");
	magicuseinfo_.magic_cool_time = 0;
	magicuseinfo_.magic_flag = false;
	magicuseinfo_.magic_position_flag = false;
	knockback_.knockbackflag = false;
	knockback_.knockback = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale_ = D3DXVECTOR3(60.0f, 60.0f, 60.0f);
	skinmesh_->SetAnimSpeed(0.0f);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixTranslation(&matrix_.position, 100.0f, 60.0f, 0.0f);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
	position_ = D3DXVECTOR3(0.0f, 0.0f, 300.0f);
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);
	moveinfomation_.basic_lowspeed = 1.0f;
	moveinfomation_.basic_middlespeed = 1.75f;
	moveinfomation_.basic_highspeed = 2.5f;
	moveinfomation_.variable_movespeed = 0.5f;
	movecolisioninfo_.colision01.r = 36.0f;
	movecolisioninfo_.colision02.r = 28.0f;
	movecolisioninfo_.center_to_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	movecolisioninfo_.hit_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	movecolisioninfo_.hit_vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	movecolisioninfo_.two_radius = 0.0f;
	AxisMove_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void BossMonster::Update()
{
	movecolisioninfo_.colision01.modelpos = position_;
	D3DXMATRIX getmtx = SceneGame::GetPlayer()->GetPlayerPosMatrix();
	movecolisioninfo_.colision02.modelpos = SceneGame::GetPlayer()->GetPlayerPosition();
	movecheckcolision_ = movecolision_->Collision_detection_of_Sphere_and_Sphere(movecolisioninfo_);
	//movecheckcolision_ = SceneGame::GetPlayer()->GetColisionFlag();
	//ImGui::GetFlagCheck("PlayerColision", movecheckcolision_);
	D3DXVECTOR3 PlayerPosition = SceneGame::GetPlayer()->GetPlayerPosition();
	AxisMove_ = PlayerPosition - position_;
	D3DXVec3Normalize(&AxisMove_, &AxisMove_);

	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);

	float rotation = atan2f(AxisMove_.x, AxisMove_.z);
	rotation = rotation + D3DX_PI;

	if (!cameraflag_)
	{
		if (camerastartcount_ < 250)
		{
			skinmesh_->SetAnimSpeed(2.0f);
		}
		else
		{
			skinmesh_->SetAnimSpeed(0.0f);
			skinmesh_->MyChangeAnim(0.0);
			camerastartcount_ = 0;
		}

		camerastartcount_++;
	}
	if (cameraflag_)
	{
		statusmanager_->Update(this);

		if (magicuseinfo_.magic_flag)
		{
			SceneGame::GetBossMagicAEfk()->SetIsDrawing(false);
			SceneGame::GetBossMagicB_1Efk()->SetIsDrawing(false);
			SceneGame::GetBossMagicCEfk()->SetIsDrawing(false);
		}
		if (movecheckcolision_)
		{
			attackframe_ = 0;
			magicuseinfo_.magic_flag = true;
			attack_->Update(this);
		}
		else
		{
			attackframe_++;
			if (attackframe_ > 50)
			{
				magicuseinfo_.magic_flag = false;
				if (movestatecheck_)
				{
					skinmesh_->MyChangeAnim(63.3);
					movestatecheck_ = false;
				}
				else
				{
					if (magicuseinfo_.magic_cool_time < 600)
					{
						bosspattern_->Update(this);
					}
					else if (magicuseinfo_.magic_cool_time > 600)
					{
						magic_->Update(this);
					}
				}
			}

			magicuseinfo_.magic_cool_time++;
		}
	}

	if (knockback_.knockbackflag)
	{
		position_ += Getknockback() * 30.0f;
	}

	GetPos_ = position_;
	D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);
	D3DXMatrixRotationY(&matrix_.rotation, rotation);
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);
	GetRotation_ = matrix_.rotation;
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	skinmesh_->Update(matrix_.world);
}

void BossMonster::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	device->LightEnable(0, true);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	skinmesh_->Draw(device);
}

void BossMonster::Uninit()
{
	skinmesh_->Release();
	delete skinmesh_;
	delete statusmanager_;
	delete magic_;
	delete attack_;
	delete movecolision_;
	delete bosspattern_;
}

void BossMonster::Damage(float _damage, D3DXVECTOR3 _knockback)
{
	knockback_.knockback = _knockback;
	life_ -= _damage;
}

void BossMonster::SetPosition(D3DXVECTOR3 _pos)
{
	position_ += _pos;
}

void BossMonster::SetRotation(float _rotation)
{
	D3DXMatrixRotationY(&matrix_.rotation, _rotation);
}

void BossMonster::SetMoveFlagON()
{
	movestatecheck_ = true;
}

void BossMonster::SetMagicCoolTime(int _MagicCoolTime)
{
	magicuseinfo_.magic_cool_time = _MagicCoolTime;
}

void BossMonster::SetMagicPositionFlag(bool _SetMagicPositionFlag)
{
	magicuseinfo_.magic_position_flag = _SetMagicPositionFlag;
}

void BossMonster::SetCameraMoveFlag(bool _cameraflag)
{
	cameraflag_ = _cameraflag;
}

void BossMonster::SetKnockBackFlag(bool _knockbackflag)
{
	knockback_.knockbackflag = _knockbackflag;
}

void BossMonster::ChangeBossMonsterMovePattern(int _pattern, BossMonsterPattern * _bossmonsterpattern)
{
	bosspattern_ = _bossmonsterpattern;
	StateNum_ = _pattern;
}

void BossMonster::ChangeBossMonsterMagicPattern(BossMonsterMagicPattern * _bossmonstermagicpattern)
{
	magic_ = _bossmonstermagicpattern;
}

void BossMonster::ChangeBossMonsterAttackPattern(BossMonsterAttackPattern * _bossmonsterattackpattern)
{
	attack_ = _bossmonsterattackpattern;
}

void BossMonster::SetAxisMove(D3DXVECTOR3 _AxisMove)
{
	AxisMove_ = _AxisMove;
}

D3DXVECTOR3 BossMonster::GetAxisMove()
{
	return AxisMove_;
}

bool BossMonster::GetMagicPositionFlag()
{
	return magicuseinfo_.magic_position_flag;
}

bool BossMonster::GetMagicFlag()
{
	return magicuseinfo_.magic_flag;
}

bool BossMonster::GetMoveFlag()
{
	return movestatecheck_;
}

bool BossMonster::GetCameraMoveFlag()
{
	return cameraflag_;
}

bool BossMonster::GetknockbackFlag()
{
	return knockback_.knockbackflag;
}

D3DXVECTOR3 BossMonster::Getknockback()
{
	D3DXVec3Normalize(&knockback_.knockback, &knockback_.knockback);
	return knockback_.knockback;
}

int BossMonster::GetMagicCoolTime()
{
	return magicuseinfo_.magic_cool_time;
}

D3DXVECTOR3 BossMonster::GetPosition()
{
	return GetPos_;
}

D3DXMATRIX & BossMonster::GetPositionMatrix()
{
	return matrix_.position;
}

CSkinMesh * BossMonster::GetSkinMesh()
{
	return skinmesh_;
}

float& BossMonster::GetMoveLowSpeed()
{
	return moveinfomation_.basic_lowspeed;
}

float& BossMonster::GetMoveHighSpeed()
{
	return moveinfomation_.basic_highspeed;
}

float & BossMonster::GetMoveMiddleSpeed()
{
	return moveinfomation_.basic_middlespeed;
}

float& BossMonster::GetMoveVariableSpeed()
{
	return moveinfomation_.variable_movespeed;
}

BossMonster * BossMonster::Create(float _Max_Mana, float _Max_Life)
{
	BossMonster* createboss = new BossMonster(_Max_Mana, _Max_Life);
	createboss->Init();
	return createboss;
}

bool BossMonster::GetMoveColisionCheck()
{
	return movecheckcolision_;
}

int BossMonster::GetStateNum()
{
	return StateNum_;
}

bool BossMonster::GetAttackState()
{
	return nowattack_;
}

void BossMonster::SetAttackState(bool _attack)
{
	nowattack_ = _attack;
}

bool BossMonster::GetMagicState()
{
	return magicsetflag_;
}

void BossMonster::SetMagicState(bool _magicstate)
{
	magicsetflag_ = _magicstate;
}
