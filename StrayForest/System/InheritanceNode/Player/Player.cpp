#include "Player.h"
#include "../Camera.h"
#include "../../../main.h"

void Player::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/RPGPlayer.x");
	
	position_ = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	scale_ = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixIdentity(&this->matrix_.position);
	D3DXMatrixIdentity(&this->matrix_.rotation);
	D3DXMatrixIdentity(&this->matrix_.scale);
	D3DXMatrixIdentity(&this->matrix_.world);

	//D3DXQuaternionIdentity(&Quaternion_);
}

void Player::Update()
{
	D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);
	D3DXMatrixRotationYawPitchRoll(&matrix_.rotation, 0.0f,0.0f,0.0f);
	//D3DXQUATERNION quaternion;
	//D3DXQuaternionRotationAxis();
	//D3DXQuaternionMultiply();

	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	ImGui::GetMatrixInfomation("Player", matrix_.world);
	skinmesh_->Update(matrix_.world);
}

void Player::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	//D3DXMatrixRotationAxis();
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
