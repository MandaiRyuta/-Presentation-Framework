#include "PlayerState.h"
#include "../../../LoadManager/TextureLoder.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../Player/PlayerItem/PlayerWeapon.h"
#include "../../BossMonster/BossMonster.h"
#include "../../../colision/SphereColision.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Player.h"
#include "../../../Polygon3D.h"
#include "../../../Polygon2D.h"
#include "../../../Renderer/GameManager.h"
#include "../../../System/InheritanceNode/Camera.h"
#include "../../MyEffekseer/MyEffekseer.h"
#include <random>

PlayerState::PlayerState(Player* _player)
	: alphacolor_(1)
	, flag_(true)
	, attackflag_(false)
	, frame_(0)
	, damegeflag_(false)
{
	D3DXMatrixIdentity(&LeftHand_.position);
	D3DXMatrixIdentity(&LeftHand_.rotation);
	D3DXMatrixIdentity(&LeftHand_.scale);
	D3DXMatrixIdentity(&LeftHand_.world);
	set = D3DXVECTOR3(-15.04f, 0.88f, -14.04f);
	enemyweponscale_ = 7.979f;
	playerhitpos_ = D3DXVECTOR3(0.0f, 27.42f, 0.0f);
	playerhitscale_ = 15.426f;
	damegecount_ = 0;
	
}

PlayerState::~PlayerState()
{
}

void PlayerState::Update(Player * _player)
{
	D3DXVECTOR3 ColisionPlayer,ColisionEnemy;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> PatternA(150.0, 250.0);
	std::uniform_real_distribution<double> PatternB(200.0, 300.0);
	std::uniform_real_distribution<double> PatternC(250.0, 450.0);
	bool check;

	D3DXMATRIX LeftHand = SceneGame::GetBossMonster()->GetSkinMesh()->GetBoneMatrix("Armature_Mutant_LeftHand");
	LeftHand_.world = LeftHand_.scale * LeftHand_.rotation * LeftHand_.position * LeftHand;
	D3DXVec3TransformCoord(&ColisionEnemy,&set,&LeftHand_.world);
	D3DXVec3TransformCoord(&ColisionPlayer, &playerhitpos_, &_player->GetPlayerPosMatrix());
	attackcheck_.colision01.modelpos = ColisionEnemy;
	attackcheck_.colision01.r = enemyweponscale_;
	attackcheck_.colision02.modelpos = ColisionPlayer;
	attackcheck_.colision02.r = playerhitscale_;
	check = attackcolision_.Collision_detection_of_Sphere_and_Sphere(attackcheck_);
	SceneGame::GetBossAttackEfk()->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	SceneGame::GetBossAttackEfk()->SetPosition(ColisionPlayer);
	SceneGame::GetBossAttackEfk()->SetFrameCount(1.0f);
	
	if (!_player->GetDiffenceMode())
	{
		if (check)
		{
			SceneGame::GetBossAttackEfk()->SetIsDrawing(true);
			D3DXVECTOR3 knockbackpos = _player->GetPlayerPosition() - SceneGame::GetBossMonster()->Position();
			attackflag_ = true;
			_player->GetSkinMesh()->MyChangeAnim(30.0);
			_player->GetSkinMesh()->SetAnimSpeed(3.0f);
			damegeflag_ = true;
			if (damegecount_ == 0)
			{
				if (SceneGame::GetBossMonster()->GetStateNum() == 0)
				{
					float setdamege = (float)PatternA(mt);
					_player->Damage(setdamege, knockbackpos);

				}
				if (SceneGame::GetBossMonster()->GetStateNum() == 1)
				{
					float setdamege = (float)PatternB(mt);
					_player->Damage(setdamege, knockbackpos);
				}
				if (SceneGame::GetBossMonster()->GetStateNum() == 2)
				{
					float setdamege = (float)PatternC(mt);
					_player->Damage(setdamege, knockbackpos);
				}
			}
			damegecount_++;
		}
		else
		{
			if (damegecount_ > 0)
			{
				damegecount_ = 0;
			}
			_player->Damage(0.0f, D3DXVECTOR3(0.0f,0.0f,0.0f));
		}
	}
	
	if (damegeflag_)
	{
		if (damegeframe_ <= 30)
		{
			damegeframe_++;
		}
		else
		{
			_player->SetMobileMotion(true);
			damegeframe_ = 0;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			damegeflag_ = false;
		}
	}

	if (attackflag_)
	{
		if (frame_ < 60)
		{
			frame_++;
		}
		else
		{
			SceneGame::GetBossAttackEfk()->SetIsDrawing(false);
			frame_ = 0;
			attackflag_ = false;
		}
	}

	frame_++;
	if (_player->GetLife() < _player->GetMaxLife() * 0.45f)
	{
		if (flag_)
		{
			if (alphacolor_ >= 128)
			{
				flag_ = false;
			}
			alphacolor_++;
		}
		else
		{
			if (alphacolor_ <= 1)
			{
				flag_ = true;
			}
			alphacolor_--;
		}
		SceneGame::GetDamegeEffect()->SetColor(D3DCOLOR_RGBA(255, 0, 0, alphacolor_));
	}
	else
	{
		SceneGame::GetDamegeEffect()->SetColor(D3DCOLOR_RGBA(255, 0, 0, 0));
	}

	_player->addLife(_player->GetMaxLife() * 0.0001f);
	_player->addmana(_player->GetMaxMana() * 0.00005f);

	SceneGame::GetHealthBar()->StatusSetUp(_player->GetLife(), _player->GetMaxLife());
	SceneGame::GetManaBar()->StatusSetUp(_player->GetMana(), _player->GetMaxMana());
}

