#include "WinPlayer.h"
#include "../MeshFiled.h"
#include "../../../SceneManager/InheritanceNode/SceneWinResult.h"

WinPlayer::WinPlayer(int _priority)
	: GameObjectManager(_priority)
	, winactiontime_(0)
{
}

WinPlayer::~WinPlayer()
{
}

void WinPlayer::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Player.x");
	skinmesh_->MyChangeAnim(27.5);
	skinmesh_->SetAnimSpeed(2.0f);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
	D3DXMatrixScaling(&matrix_.scale, 30.0f,30.0f,30.0f);
}

void WinPlayer::Update()
{
	position_.y = SceneWinResult::GetMeshFiled()->GetHeight(position_);
	D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);

	if (winactiontime_ < 190)
	{
		winactiontime_++;
	}
	else
	{
		skinmesh_->SetAnimSpeed(0.0f);
		winactiontime_ = 0;
	}

	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	skinmesh_->Update(matrix_.world);
}

void WinPlayer::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_->Draw(device);
}

void WinPlayer::Uninit()
{
	skinmesh_->Release();
	delete skinmesh_;
	skinmesh_ = nullptr;
}

WinPlayer * WinPlayer::Create(int _priority)
{
	WinPlayer* WinResultPlayer = new WinPlayer(_priority);
	WinResultPlayer->Init();
	return WinResultPlayer;
}

D3DXVECTOR3 WinPlayer::GetPlayerPos()
{
	return position_;
}