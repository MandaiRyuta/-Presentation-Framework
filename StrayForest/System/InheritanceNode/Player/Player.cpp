#include "Player.h"
#include "../../../main.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../MeshFiled.h"
#include "../../../InputManager/input.h"
#include "../../../Renderer/GameManager.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "PlayerMove\PlayerMoveManager.h"
#include "PlayerMove\PlayerMove.h"
#include "PlayerAttack\PlayerAttackManager.h"
#include "PlayerBuffState\PlayerBuffStateManager.h"
#include "PlayerDiffence\PlayerDiffenceManager.h"
#include "PlayerMagic\PlayerMagicManager.h"
#include "PlayerBuffState\PlayerBuffStateManager.h"
#include "PlayerItem\ItemList.h"
#include "PlayerItem\PlayerShiled.h"
#include "PlayerItem\PlayerWeapon.h"
#include "PlayerMagic\PlayerMagic.h"
#include "PlayerDiffence\PlayerDiffence.h"
#include "PlayerBuffState\PlayerBuff.h"
#include "PlayerAttack\PlayerNomalAttack.h"
D3DXMATRIX Player::world_;
D3DXMATRIX Player::rot_;
D3DXMATRIX Player::pos_;

Player::Player() 
	: GameObjectManager(OBJ_3D_MODEL)
	, movemanager_(new PlayerMove)
	, magicmanager_(new PlayerMagic(this))
	, attackmanager_(new PlayerNomalAttack(this))
	, diffencemanager_(new PlayerDiffence(this))
	, buffmanager_(new PlayerBuff(this))
	, playeraction_(STATE)
	, StateMode_(false)
{
}
void Player::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Player.x");
	
	scale_ = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	skinmesh_->SetAnimSpeed(1.0f);
	D3DXMatrixIdentity(&this->matrix_.position);
	D3DXMatrixIdentity(&this->matrix_.rotation);
	D3DXMatrixIdentity(&this->matrix_.scale);
	D3DXMatrixIdentity(&this->matrix_.world);
	item_ = new ItemList;
	item_->add(new Sword, new Shiled);
	item_->Init(device);
}

void Player::Update()
{
	keyboard_ = GameManager::GetKeyboard();
	item_->Update();
	ImGui::GetMatrixInfomation("Player", matrix_.world);
	attackmanager_->Update(this);
	skinmesh_->Update(matrix_.world);
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);
	movemanager_->Update(this);
	magicmanager_->Update(this);
	diffencemanager_->Update(this);
	buffmanager_->Update(this);
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	pos_ = matrix_.position;
	rot_ = matrix_.rotation;
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
	D3DXMATRIX mtxSword, mtxShiled;
	mtxSword = skinmesh_->GetBoneMatrix("Bip001_001_Bip001_R_Hand");
	mtxShiled = skinmesh_->GetBoneMatrix("Bip001_001_Bip001_L_Hand");
	item_->ShiledDraw(device,mtxShiled);
	item_->SwordDraw(device,mtxSword);
	skinmesh_->Draw(device);
}

void Player::Uninit()
{
	skinmesh_->Release();
	item_->Uninit();
	delete item_;
	delete skinmesh_;
	delete movemanager_;
	delete attackmanager_;
	delete buffmanager_;
	delete diffencemanager_;
	delete magicmanager_;
}

void Player::Damage(int _damage)
{
	Life_ -= _damage;
}

void Player::Heal(double _animtrack, float _speed, int _amount)
{
	Life_ += _amount;
	
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::Attack(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::Skill(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::Magic(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::Buff(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

void Player::DeBuff(double _animtrack, double _speed)
{
	//skinmesh_->SetAnimSpeed(_speed);
	skinmesh_->MyChangeAnim(_animtrack);
}

Player * Player::Create()
{
	Player* CreatePlayer = new Player;
	CreatePlayer->Init();
	return CreatePlayer;
}

void Player::ChangeMovePattern(PlayerMoveManager * _move)
{
	delete movemanager_;
	movemanager_ = _move;
}

void Player::ChangeAttackPattern(PlayerMagicManager * _magic)
{
	delete magicmanager_;
	magicmanager_ = _magic;
}

void Player::ChangeMagicPattern(PlayerAttackManager * _attack)
{
	delete attackmanager_;
	attackmanager_ = _attack;
}

void Player::ChangeBuffMode(PlayerBuffStateManager * _buff)
{
	delete buffmanager_;
	buffmanager_ = _buff;
}

void Player::ChangeDiffencePattern(PlayerDiffenceManager * _diffence)
{
	delete diffencemanager_;
	diffencemanager_ = _diffence;
}

CInputKeyboard * Player::GetKeyboard()
{
	return keyboard_;
}

void Player::SetPlayerMatrix(D3DXMATRIX _world)
{
	matrix_.world = _world;
}

void Player::SetPlayerPosMatrix(D3DXMATRIX _pos)
{
	matrix_.position = _pos;
}

void Player::SetPlayerRotMatrix(D3DXMATRIX _rot)
{
	matrix_.rotation = _rot;
}

void Player::SetActionPattern(ACTIONPATTERN _action)
{
	playeraction_ = _action;
}

void Player::SetStateMode(bool _StateMode)
{
}

bool Player::GetStateMode()
{
	return StateMode_;
}

ACTIONPATTERN& Player::GetActionPattern()
{
	return playeraction_;
}

D3DXMATRIX & Player::GetPlayerMatrix()
{
	return world_;
}

D3DXMATRIX & Player::GetPlayerPosMatrix()
{
	return pos_;
}

D3DXMATRIX & Player::GetPlayerRotMatrix()
{
	return rot_;
}