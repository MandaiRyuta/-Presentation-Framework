#include "BossEnemy.h"
#include "BossAttack\BossAttackDamageManager.h"
#include "BossSkill\BossEnemySkillManager.h"
#include "BossMagic\BossEnemyMagicManager.h"
#include "BossMove\BossEnemyMoveManager.h"
#include "BossStatus\BossEnemyStateManager.h"
#include "BossDeffence\BossEnemyDeffenceManager.h"
#include "BossMove\BossEnemyMove.h"
#include "BossMove\BossEnemyRotation.h"
#include "BossAttack\BossEnemyAttack01.h"
#include "BossAttack\BossEnemyAttack02.h"
#include "BossAttack\BossEnemyAttack03.h"
#include "BossDeffence\BossEnemyDeffencePattern01.h"
#include "BossDeffence\BossEnemyDeffencePattern02.h"
#include "BossMagic\BossEnemyMagic01.h"
#include "BossMagic\BossEnemyMagic02.h"
#include "BossMagic\BossEnemyMagic03.h"
#include "BossSkill\BossEnemySkill01.h"
#include "BossSkill\BossEnemySkill02.h"
#include "BossSkill\BossEnemySkill03.h"
#include "BossStatus\BossEnemyHealth.h"
#include "BossStatus\BossEnemyMana.h"
#include "BossStatus\BossEnemyPower.h"

D3DXMATRIX BossEnemy::world_;

void BossEnemy::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/RPGPlayer.x");

	scale_ = D3DXVECTOR3(60.0f, 60.0f, 60.0f);

	move_ = new BossEnemyMove;
	rotate_ = new BossEnemyRotation;
	attack01_ = new BossEnemyAttack01;
	attack02_ = new BossEnemyAttack02;
	attack03_ = new BossEnemyAttack03;
	deffence01_ = new BossEnemyDeffencePattern01;
	deffence02_ = new BossEnemyDeffencePattern02;
	magic01_ = new BossEnemyMagic01;
	magic02_ = new BossEnemyMagic02;
	magic03_ = new BossEnemyMagic03;
	healthstate_ = new BossEnemyHealth;
	manastate_ = new BossEnemyMana;
	powerstate_ = new BossEnemyPower;

	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
}

void BossEnemy::Update()
{	
	skinmesh_->Update(matrix_.world);
	move_->Update(skinmesh_, matrix_.position, matrix_.rotation, movestate_);
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);

	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;

	world_ = matrix_.world;
}

void BossEnemy::Draw()
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

void BossEnemy::Uninit()
{
	skinmesh_->Release();
	delete skinmesh_;
}

BossEnemy * BossEnemy::Create(double _Health, double _mana)
{
	BossEnemy* CreateBoss = new BossEnemy(_Health, _mana);
	CreateBoss->Init();
	return CreateBoss;
}

D3DXMATRIX BossEnemy::GetBossMatrix()
{
	return world_;
}
