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

BossMonster::BossMonster(int _Max_Life, int _Max_Mana)
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
	basic_lowspeed_ = 0.5f;
	basic_highspeed_ = 1.0f;
	variable_movespeed_ = 0.5f;
	movecolisioninfo_.colision01.r = 35.0f;
	movecolisioninfo_.colision02.r = 35.0f;
}

void BossMonster::Update()
{
	movecolisioninfo_.colision01.modelpos = position_;
	D3DXMATRIX getmtx = SceneGame::GetPlayer()->GetPlayerPosMatrix();
	movecolisioninfo_.colision02.modelpos = D3DXVECTOR3(SceneGame::GetPlayer()->GetPlayerPosMatrix()._41,SceneGame::GetPlayer()->GetPlayerBodyMatrix()._42,SceneGame::GetPlayer()->GetPlayerBodyMatrix()._43);
	bool colisioncheck = movecolision_->Collision_detection_of_Sphere_and_Sphere(movecolisioninfo_);
	movecheckcolision_ = colisioncheck;

	statusmanager_->Update(this);

	if (magicflag_)
	{
		SceneGame::GetBossMagicAEfk()->SetIsDrawing(false);
		SceneGame::GetBossMagicB_1Efk()->SetIsDrawing(false);
		SceneGame::GetBossMagicCEfk()->SetIsDrawing(false);

	}
	if (colisioncheck)
	{
		magicflag_ = true;
		attack_->Update(this);
		skill_->Update(this);
		movecolisioninfo_.hit_vector.y = 0.0f;
		position_ += movecolisioninfo_.hit_vector;
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

	D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);

	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);
	GetRotation_ = matrix_.rotation;
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	skinmesh_->SetAnimSpeed(1.0f);
	skinmesh_->Update(matrix_.world);
	GetPos_ = D3DXVECTOR3(matrix_.position._41, matrix_.position._42, matrix_.position._43);
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
	delete magic_;
	delete skill_;
	delete attack_;
	delete movecolision_;
	delete bosspattern_;
}

void BossMonster::Damage(float _damage)
{
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

void BossMonster::ChangeBossMonsterMovePattern(BossMonsterPattern * _bossmonsterpattern)
{
	bosspattern_ = _bossmonsterpattern;
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

bool BossMonster::GetMagicFlag()
{
	return magicflag_;
}

D3DXMATRIX & BossMonster::GetPositionMatrix()
{
	return matrix_.position;
}

CSkinMesh * BossMonster::GetSkinMesh()
{
	return skinmesh_;
}

SphereColision * BossMonster::GetMoveColision()
{
	return movecolision_;
}

Entity::SphereColision& BossMonster::GetMoveColisionInfo()
{
	return movecolisioninfo_;
}

float& BossMonster::GetMoveLowSpeed()
{
	return basic_lowspeed_;
}

float& BossMonster::GetMoveHighSpeed()
{
	return basic_highspeed_;
}

float& BossMonster::GetMoveVariableSpeed()
{
	return variable_movespeed_;
}

const bool & BossMonster::GetMoveHitColision()
{
	return movecheckcolision_;
}

BossMonster * BossMonster::Create(int _Max_Mana, int _Max_Life)
{
	BossMonster* createboss = new BossMonster(_Max_Mana, _Max_Life);
	createboss->Init();
	return createboss;
}
