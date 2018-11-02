#include "Player.h"
#include "../Camera.h"
#include "../../../main.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../MeshFiled.h"

D3DXMATRIX Player::world_;

void Player::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/RPGPlayer.x");
	
	scale_ = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

	move_ = new PlayerMoveManager;
	move_->Init();
	D3DXMatrixIdentity(&this->matrix_.position);
	D3DXMatrixIdentity(&this->matrix_.rotation);
	D3DXMatrixIdentity(&this->matrix_.scale);
	D3DXMatrixIdentity(&this->matrix_.world);
}

void Player::Update()
{
	ImGui::GetMatrixInfomation("Player", matrix_.world);
	skinmesh_->Update(matrix_.world);
	move_->Update(skinmesh_,matrix_.position,matrix_.rotation);
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);

	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	
	world_ = matrix_.world;
}

void Player::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	//裏面カリング(ポリゴンの裏面を描画しない)
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// フィルタ設定
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//ライトを無効にする
	device->LightEnable(0, true);
	// ライトの計算処理をしない
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//マテリアルの設定
	device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	skinmesh_->Draw(device);
}

void Player::Uninit()
{
	skinmesh_->Release();
	delete skinmesh_;
}

Player * Player::Create()
{
	Player* CreatePlayer = new Player;
	CreatePlayer->Init();
	return CreatePlayer;
}

D3DXMATRIX Player::GetPlayerMatrix()
{
	return world_;
}
