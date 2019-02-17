#include "BossStatus.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../BossMonster/BossMonster.h"
#include "../../../colision/SphereColision.h"
#include "../../MyEffekseer/MyEffekseer.h"
#include "../.././/Player/PlayerItem/PlayerWeapon.h"
#include <random>

BossStatus::BossStatus()
	: frame_(0)
	, effectdrawflag_(false)
	, damegeflag_(false)
	, damegeframe_(0)
	, damegeactiioncount_(0)
	, damegeactionflag_(false)
{
	weponcolisionset_ = D3DXVECTOR3(0.0f, 2.65f, 0.0f);
	bosshitpos_ = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	damegecount_ = 0;
	PlayerHitScale_ = 2.0f;
	EnemyHitScale_ = 33.551f;
}

BossStatus::~BossStatus()
{
}

void BossStatus::Update(BossMonster * _bossmonster)
{
	D3DXVECTOR3 ColisionPlayer, ColisionEnemy;
	bool check;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> AttackDamage(110.0, 140.0);
	D3DXMATRIX LeftHand = SceneGame::GetPlayerSword()->GetMtxWorld();

	D3DXVec3TransformCoord(&ColisionPlayer, &D3DXVECTOR3(weponcolisionset_.x, weponcolisionset_.y, weponcolisionset_.z), &LeftHand);
	D3DXVec3TransformCoord(&ColisionEnemy, &D3DXVECTOR3(bosshitpos_.x, bosshitpos_.y, bosshitpos_.z), &_bossmonster->GetPositionMatrix());
	
	attackcheck_.colision01.modelpos = ColisionPlayer;
	attackcheck_.colision01.r = PlayerHitScale_;
	attackcheck_.colision02.modelpos = ColisionEnemy;
	attackcheck_.colision02.r = EnemyHitScale_;

	check = attackcolision_.Collision_detection_of_Sphere_and_Sphere(attackcheck_);
	
	SceneGame::GetDamegeEffectONEfk()->SetScale(D3DXVECTOR3(25.0f, 25.0f, 25.0f));
	SceneGame::GetDamegeEffectONEfk()->SetPosition(ColisionEnemy);
	SceneGame::GetDamegeEffectONEfk()->SetFrameCount(2.0f);

	if (check)
	{
		D3DXVECTOR3 knockbackpos = _bossmonster->GetPosition() - SceneGame::GetPlayer()->GetPlayerPosition();
		if (damegecount_ == 0)
		{
			damegeactionflag_ = true;
			SceneGame::GetDamegeEffectONEfk()->SetIsDrawing(true);
			float setdamege = (float)AttackDamage(mt);
			_bossmonster->Damage(setdamege, knockbackpos);
			effectdrawflag_ = true;
		}
		damegecount_++;
	}
	else
	{
		damegecount_ = 0;
		_bossmonster->Damage(0.0f, D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	if (damegeactionflag_)
	{
		damegeactiioncount_ += 1;
		damegeactionflag_ = false;
	}

	if (damegeactiioncount_ >= 10)
	{
		damegeactiioncount_ = 0;
		damegeflag_ = true;
		_bossmonster->GetSkinMesh()->MyChangeAnim(411.5);
	}

	if (damegeflag_)
	{
		_bossmonster->SetKnockBackFlag(true);

		if (damegeframe_ <= 60)
		{
			damegeframe_++;
		}
		else
		{
			damegeflag_ = false;
			damegeframe_ = 0;
			_bossmonster->GetSkinMesh()->MyChangeAnim(63.3);
			_bossmonster->SetKnockBackFlag(false);
		}
	}

	if (frame_ >= 8)
	{
		damegeactiioncount_ += 1;
		effectdrawflag_ = false;
		SceneGame::GetDamegeEffectONEfk()->SetIsDrawing(false);
		frame_ = 0;
	}

	if (effectdrawflag_)
	{
		frame_++;
	}
}
