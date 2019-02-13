#include "ChutorialBoss.h"
#include "../MeshFiled.h"
#include "../../../SceneManager/InheritanceNode/SceneChutorial.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
ChutorialBoss::ChutorialBoss()
	: GameObjectManager(0)
	, framecount_(0)
{
}

ChutorialBoss::~ChutorialBoss()
{
}

void ChutorialBoss::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Boss.x");
	skinmesh_->SetAnimSpeed(1.0f);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
	D3DXMatrixScaling(&matrix_.scale, 60.0f, 60.0f, 60.0f);
	D3DXMatrixTranslation(&matrix_.position, 0.0f, 0.0f, 300.0f);
	position_ = D3DXVECTOR3(0.0f, 0.0f, 300.0f);
	D3DXVECTOR3 PlayerPos = SceneChutorial::GetChutorialPlayer()->GetPosition();
	D3DXVECTOR3 AxisSet = PlayerPos - D3DXVECTOR3(position_.x,0.0f,position_.z);
	rotation_ = atan2f(AxisSet.x, AxisSet.z);
	rotation_ = rotation_ + D3DX_PI;
	framecount_ = 0;
}

void ChutorialBoss::Update()
{
	skinmesh_->SetAnimSpeed(1.0f);
	if (framecount_ > 540)
	{
		skinmesh_->SetAnimSpeed(1.0f);
		skinmesh_->MyChangeAnim(0.0);
		framecount_ = 0;
	}
	position_.y = SceneChutorial::GetMeshFiled()->GetHeight(position_);
	D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);
	D3DXMatrixRotationY(&matrix_.rotation, rotation_);
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;

	skinmesh_->Update(matrix_.world);
	framecount_++;
}

void ChutorialBoss::Draw()
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

void ChutorialBoss::Uninit()
{
	skinmesh_->Release();
	delete skinmesh_;
	skinmesh_ = nullptr;
}

ChutorialBoss * ChutorialBoss::Create()
{
	ChutorialBoss* ChutoBoss = new ChutorialBoss;
	ChutoBoss->Init();
	return ChutoBoss;
}

D3DXVECTOR3 ChutorialBoss::GetPosition()
{
	return position_;
}
