#include "BossMonster.h"
#include "BossMonsterAttack\BossMonsterAttackPattern.h"
#include "BossMonsterMagic\BossMonsterMagicPattern.h"
#include "BossMonsterPatterns\BossMonsterPattern.h"
#include "BossMonsterSkill\BossMonsterSkillPattern.h"

void BossMonster::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/RPGPlayer.x");

	scale_ = D3DXVECTOR3(60.0f, 60.0f, 60.0f);

	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
}

void BossMonster::Update()
{
	skinmesh_->Update(matrix_.world);

	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);

	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
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

void BossMonster::Damage(double _damage)
{
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

void BossMonster::ChangeBossMonsterMovePattern(BossMonsterPattern * _bossmonsterpattern)
{
}

void BossMonster::ChangeBossMonsterSkillPattern(BossMonsterSkillPattern * _bossmonsterskillpattern)
{
}

void BossMonster::ChangeBossMonsterMagicPattern(BossMonsterMagicPattern * _bossmonstermagicpattern)
{
}

void BossMonster::ChangeBossMonsterAttackPattern(BossMonsterAttackPattern * _bossmonsterattackpattern)
{
}

BossMonster * BossMonster::Create()
{
	BossMonster* createboss = new BossMonster;
	createboss->Init();
	return createboss;
}
