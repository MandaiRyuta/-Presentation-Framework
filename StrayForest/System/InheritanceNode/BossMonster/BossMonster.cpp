#include "BossMonster.h"
#include "BossMonsterPatterns\BossMonsterPatternA.h"
#include "../MeshFiled.h"
#include "BossMonsterAttack\BossMonsterAttackPattern.h"
#include "BossMonsterMagic\BossMonsterMagicPattern.h"
#include "BossMonsterSkill\BossMonsterSkillPattern.h"
#include "BossMonsterPatterns\BossMonsterPattern.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "BossMonsterAttack\BossMonsterAttackPatternA.h"
#include "../Player/Player.h"
#include "BossStatus\BossStatusManager.h"
#include "BossStatus\BossStatus.h"
#include "BossMonsterMagic\BossMonsterMagicPatternA.h"

D3DXVECTOR3 BossMonster::GetPos_;
Entity::MATRIX3D BossMonster::GetMatrix_;
D3DXMATRIX BossMonster::GetRotation_;

BossMonster::BossMonster(float _Max_Life, float _Max_Mana)
	: GameObjectManager(0)
	, bosspattern_(new BossMonsterPatternNone)
	, magic_(new BossMonsterMagicPatternA)
	, skill_(new BossMonsterSkillNone)
	, attack_(new BossMonsterAttackPatternA)
	, max_life_(_Max_Life)
	, life_(_Max_Life)
	, max_mana_(_Max_Mana)
	, mana_(_Max_Mana)
	, movecolision_(new SphereColision)
	, statusmanager_(new BossStatus)
	, movecheckcolision_(false)
	, movestatecheck_(false)
	, MagicCoolTime_(0)
	, magicflag_(false)
	, cameraflag_(false)
	, magicpositonflag_(false)
	, camerastartcount_(0)
	, StateNum_(0)
	, knockbackflag_(false)
{
}

void BossMonster::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Boss.x");
	scale_ = D3DXVECTOR3(60.0f, 60.0f, 60.0f);
	skinmesh_->SetAnimSpeed(0.0f);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixTranslation(&matrix_.position, 100.0f, 60.0f, 0.0f);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
	position_ = D3DXVECTOR3(0.0f, 0.0f, 300.0f);
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);
	basic_lowspeed_ = 1.0f;
	basic_middlespeed_ = 1.75f;
	basic_highspeed_ = 2.5f;
	variable_movespeed_ = 0.5f;
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
		//skinmesh_->SetAnimSpeed(2.0f);
		statusmanager_->Update(this);

		if (magicflag_)
		{
			SceneGame::GetBossMagicAEfk()->SetIsDrawing(false);
			SceneGame::GetBossMagicB_1Efk()->SetIsDrawing(false);
			SceneGame::GetBossMagicCEfk()->SetIsDrawing(false);
		}
		if (movecheckcolision_)
		{
			magicflag_ = true;
			attack_->Update(this);
			skill_->Update(this);
		}
		else
		{
			magicflag_ = false;
			if (movestatecheck_)
			{
				skinmesh_->MyChangeAnim(63.3);
				movestatecheck_ = false;
			}
			else
			{
				if (MagicCoolTime_ < 600)
				{
					bosspattern_->Update(this);
				}
				else if (MagicCoolTime_ > 600)
				{
					magic_->Update(this);
				}
			}

			MagicCoolTime_++;
		}
	}

	if (knockbackflag_)
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
	//コリジョンの確認
	if (cameraflag_)
	{
		statusmanager_->Draw();
	}
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
	delete skill_;
	delete attack_;
	delete movecolision_;
	delete bosspattern_;
}

void BossMonster::Damage(float _damage, D3DXVECTOR3 knockback)
{
	knockback_ = knockback;
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
	MagicCoolTime_ = _MagicCoolTime;
}

void BossMonster::SetMagicPositionFlag(bool _SetMagicPositionFlag)
{
	magicpositonflag_ = _SetMagicPositionFlag;
}

void BossMonster::SetCameraMoveFlag(bool _cameraflag)
{
	cameraflag_ = _cameraflag;
}

void BossMonster::SetKnockBackFlag(bool _knockbackflag)
{
	knockbackflag_ = _knockbackflag;
}

void BossMonster::ChangeBossMonsterMovePattern(int _pattern, BossMonsterPattern * _bossmonsterpattern)
{
	bosspattern_ = _bossmonsterpattern;
	StateNum_ = _pattern;
}

void BossMonster::ChangeBossMonsterSkillPattern(BossMonsterSkillPattern * _bossmonsterskillpattern)
{
	skill_ = _bossmonsterskillpattern;
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
	return magicpositonflag_;
}

bool BossMonster::GetMagicFlag()
{
	return magicflag_;
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
	return knockbackflag_;
}

D3DXVECTOR3 BossMonster::Getknockback()
{
	D3DXVec3Normalize(&knockback_, &knockback_);
	return knockback_;
}

int BossMonster::GetMagicCoolTime()
{
	return MagicCoolTime_;
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
	return basic_lowspeed_;
}

float& BossMonster::GetMoveHighSpeed()
{
	return basic_highspeed_;
}

float & BossMonster::GetMoveMiddleSpeed()
{
	return basic_middlespeed_;
}

float& BossMonster::GetMoveVariableSpeed()
{
	return variable_movespeed_;
}

BossMonster * BossMonster::Create(int _Max_Mana, int _Max_Life)
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
