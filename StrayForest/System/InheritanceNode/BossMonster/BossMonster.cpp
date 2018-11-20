#include "BossMonster.h"
#include "BossMonsterAttack\BossMonsterAttackPattern.h"
#include "BossMonsterMagic\BossMonsterMagicPattern.h"
#include "BossMonsterSkill\BossMonsterSkillPattern.h"
#include "BossMonsterPatterns\BossMonsterPattern.h"
#include "BossMonsterPatterns\BossMonsterPatternA.h"
D3DXVECTOR3 BossMonster::GetPos_;
Entity::MATRIX3D BossMonster::GetMatrix_;

BossMonster::BossMonster(int _Max_Life, int _Max_Mana)
	: GameObjectManager(0)
	, bosspattern_(new BossMonsterPatternA)
	, max_life_(_Max_Life)
	, life_(_Max_Life)
	, max_mana_(_Max_Mana)
	, mana_(_Max_Mana)
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
	basic_lowspeed_ = 1.0f;
	basic_highspeed_ = 2.0f;
	variable_movespeed_ = 1.0f;
}

void BossMonster::Update()
{
	skinmesh_->SetAnimSpeed(2.0f);
	skinmesh_->Update(matrix_.world);
	bosspattern_->Update(this);
	//D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
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
}

void BossMonster::Damage(int _damage)
{
	life_ -= _damage;
}

void BossMonster::SetAttack(double _animtrack, float _speed)
{

}

void BossMonster::SetMagic(double _animtrack, float _speed)
{
}

void BossMonster::SetSkill(double _animtrack, float _speed)
{
}

void BossMonster::SetPosition(D3DXVECTOR3 _pos)
{
	position_ += _pos;
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

D3DXMATRIX & BossMonster::GetPositionMatrix()
{
	return matrix_.position;
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

BossMonster * BossMonster::Create(int _Max_Mana, int _Max_Life)
{
	BossMonster* createboss = new BossMonster(_Max_Mana, _Max_Life);
	createboss->Init();
	return createboss;
}
