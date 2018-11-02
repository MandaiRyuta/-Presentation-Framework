#include "BossEnemy.h"

D3DXMATRIX BossEnemy::world_;

void BossEnemy::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/RPGPlayer.x");

	scale_ = D3DXVECTOR3(60.0f, 60.0f, 60.0f);
	
	move_ = new BossEnemyMoveManager;
	//move_->Init();
	state_ = new BossEnemyStatusManager;
	state_->Init();

	attack_ = new BossAttackDamageManager;
	attack_->Init();
	skill_ = new BossEnemySkillManager;
	skill_->Init();
	magic_ = new BossEnemyMagicManager;
	magic_->Init();


	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
}

void BossEnemy::Update()
{
	skinmesh_->Update(matrix_.world);
	move_->Update(skinmesh_, matrix_.position, matrix_.rotation);
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
