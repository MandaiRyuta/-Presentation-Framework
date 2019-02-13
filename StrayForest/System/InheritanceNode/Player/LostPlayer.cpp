#include "LostPlayer.h"
#include "../Camera.h"
#include "../MeshFiled.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../SceneManager/InheritanceNode/SceneLoseResult.h"
#include "../../../Renderer/GameManager.h"

LosePlayer::LosePlayer(int _priority)
	: GameObjectManager(_priority)
	, lostactiontime_(0)
	, deadflag_(false)
{
}

LosePlayer::~LosePlayer()
{
}

void LosePlayer::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Player.x");
	skinmesh_->MyChangeAnim(30.5);
	skinmesh_->SetAnimSpeed(2.0f);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
	D3DXMatrixScaling(&matrix_.scale, 30.0f, 30.0f, 30.0f);
}

void LosePlayer::Update()
{
	position_.y = SceneLoseResult::GetMeshFiled()->GetHeight(position_);
	D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);
	
	if (lostactiontime_ < 175)
	{
		lostactiontime_++;
		if (lostactiontime_ > 50)
		{
			deadflag_ = true;
		}
	}
	else {
		skinmesh_->SetAnimSpeed(0.0f);
		lostactiontime_ = 0;
	}
	
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	skinmesh_->Update(matrix_.world);
}

void LosePlayer::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_->Draw(device);
}

void LosePlayer::Uninit()
{
	skinmesh_->Release();
	delete skinmesh_;
	skinmesh_ = nullptr;
}

LosePlayer * LosePlayer::Create(int _priority)
{
	LosePlayer* LostResultPlayer = new LosePlayer(_priority);
	LostResultPlayer->Init();
	return LostResultPlayer;
}

D3DXVECTOR3 LosePlayer::GetPlayerPos()
{
	return position_;
}

bool LosePlayer::DeadFlag()
{
	return deadflag_;
}
