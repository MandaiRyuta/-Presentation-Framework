#include "Player.h"
#include "../../../main.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../MeshFiled.h"
#include "../../../InputManager/input.h"
#include "../../../Renderer/GameManager.h"
#include "PlayerMove\PlayerMoveManager.h"
#include "PlayerAttack\PlayerAttackManager.h"
#include "PlayerBuffState\PlayerBuffStateManager.h"
#include "PlayerDiffence\PlayerDiffenceManager.h"
#include "PlayerMagic\PlayerMagicManager.h"
#include "PlayerBuffState\PlayerBuffStateManager.h"
#include "PlayerMove\PlayerMove.h"
#include "PlayerItem\PlayerShiled.h"
#include "PlayerItem\PlayerWeapon.h"
#include "PlayerMagic\PlayerMagic.h"
#include "PlayerDiffence\PlayerDiffence.h"
#include "PlayerBuffState\PlayerBuff.h"
#include "PlayerAttack\PlayerNomalAttack.h"
#include "../MyEffekseer/MyEffekseer.h"
#include "PlayerState\PlayerStateManager.h"
#include "PlayerState\PlayerState.h"
#include "../../colision/SphereColision.h"
#include "../BossMonster/BossMonster.h"
#include "../../Polygon2D.h"
D3DXMATRIX Player::world_;
D3DXMATRIX Player::rot_;
D3DXMATRIX Player::pos_;
D3DXMATRIX Player::body_;
SphereColision* Player::AttackHitColision_ = nullptr;

Player::Player(float max_health, float max_mana, float health, float mana)
	: GameObjectManager(OBJ_3D_MODEL)
	, movemanager_(new PlayerMove)
	, magicmanager_(new PlayerMagic(this))
	, attackmanager_(new PlayerNomalAttack(this))
	, diffencemanager_(new PlayerDiffence(this))
	, buffmanager_(new PlayerBuff(this))
	, statusmanager_(new PlayerState(this))
	, playeraction_(STATE)
	, StateMode_(false)
	, spherecolision_(new SphereColision)
	, Max_Life_(max_health)
	, Max_Mana_(max_mana)
	, Life_(health)
	, Mana_(mana)
	, Diffence_(false)
	, oldPosition_(D3DXVECTOR3(0.0f,0.0f,0.0f))
	, keyframe_(400)
{
}
void Player::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	skinmesh_ = new CSkinMesh;
	skinmesh_->Init(device, "Resource/Model/Player.x");
	scale_ = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	skinmesh_->SetAnimSpeed(2.0f);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
	//item_ = new ItemList;
	//item_->add(new Sword, new Shiled);
	//item_->Init();
}

void Player::Update()
{
	Entity::SphereColision moveinfo;

	keyboard_ = GameManager::GetKeyboard();
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);

	//moveinfo.colision01.modelpos = D3DXVECTOR3(matrix_.position._41, matrix_.position._42, matrix_.position._43);
	//moveinfo.colision02.modelpos = SceneGame::GetBossMonster()->GetPosition();
	//moveinfo.colision01.r = 35.0f;
	//moveinfo.colision02.r = 35.0f;

	//bool colisioncheck = spherecolision_->Collision_detection_of_Sphere_and_Sphere(moveinfo);

	//if (colisioncheck)
	//{
	//	matrix_.position._41 += moveinfo.hit_vector.x;
	//	matrix_.position._43 += moveinfo.hit_vector.z;
	//}

	movemanager_->Update(this);
	statusmanager_->Update(this);
	magicmanager_->Update(this);
	diffencemanager_->Update(this);
	buffmanager_->Update(this);
	pos_ = matrix_.position;
	rot_ = matrix_.rotation;
	world_ = matrix_.world;
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;

	ImGui::GetMatrixInfomation("Player", matrix_.world);
	attackmanager_->Update(this);
	skinmesh_->Update(matrix_.world);

	keyframe_++;
	//item_->Update();
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
	body_ = skinmesh_->GetBoneMatrix("Bip001_001_Bip001_Head");
	SceneGame::GetPlayerShiled()->SetTargetBone(mtxShiled);
	SceneGame::GetPlayerSword()->SetTargetBone(mtxSword);
	//item_->ShiledDraw(device,mtxShiled);
	//item_->SwordDraw(device,mtxSword);
	skinmesh_->Draw(device);
}

void Player::Uninit()
{
	skinmesh_->Release();
	delete skinmesh_;
	//item_->Uninit();
	delete spherecolision_;
	//delete item_;
	delete statusmanager_;
	delete movemanager_;
	delete attackmanager_;
	delete buffmanager_;
	delete diffencemanager_;
	delete magicmanager_;
}

void Player::Damage(float _damage)
{
	Life_ -= _damage;
}

void Player::UseMana(float _mana)
{
	Mana_ -= _mana;
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

Player * Player::Create(int max_health, int max_mana, int health, int mana)
{
	Player* CreatePlayer = new Player(max_health, max_mana, health, mana);
	CreatePlayer->Init();
	return CreatePlayer;
}

void Player::ChangeMovePattern(PlayerMoveManager * _move)
{
	delete movemanager_;
	movemanager_ = _move;
}

void Player::ChangeAttackPattern(PlayerAttackManager* _attack)
{
	delete attackmanager_;
	attackmanager_ = _attack;
}

void Player::ChangeMagicPattern(PlayerMagicManager* _magic)
{
	delete magicmanager_;
	magicmanager_ = _magic;
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

CSkinMesh * Player::GetSkinMesh()
{
	return skinmesh_;
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
	StateMode_ = _StateMode;
}

void Player::SetDiffenceMode(bool _diffence)
{
	Diffence_ = _diffence;
}

void Player::SetOldPosition(D3DXVECTOR3 _pos)
{
	oldPosition_ = _pos;
}

void Player::SetKeyframe(int _keyframe)
{
	keyframe_ = _keyframe;
}

void Player::addLife(float _Life)
{
	if (Life_ < Max_Life_)
	{
		Life_ += _Life;
	}
}

void Player::addmana(float _Mana)
{
	if (Mana_ < Max_Mana_)
	{
		Mana_ += _Mana;
	}
}

int Player::GetKeyframe()
{
	return keyframe_;
}

bool Player::GetStateMode()
{
	return StateMode_;
}

bool Player::GetDiffenceMode()
{
	return Diffence_;
}

D3DXVECTOR3 Player::GetOldPosition()
{
	return oldPosition_;
}

ACTIONPATTERN& Player::GetActionPattern()
{
	return playeraction_;
}

D3DXMATRIX & Player::GetPlayerMatrix()
{
	return world_;
}

D3DXMATRIX Player::GetPlayerPosMatrix()
{
	return pos_;
}

D3DXMATRIX & Player::GetPlayerRotMatrix()
{
	return rot_;
}

D3DXMATRIX & Player::GetPlayerBodyMatrix()
{
	return body_;
}

SphereColision * Player::AttackColision()
{
	return AttackHitColision_;
}
