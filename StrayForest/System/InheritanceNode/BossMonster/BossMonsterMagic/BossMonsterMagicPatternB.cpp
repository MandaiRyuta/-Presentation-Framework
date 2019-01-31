#include "BossMonsterMagicPatternB.h"
#include "../BossMonster.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MyEffekseer/MyEffekseer.h"
#include "../../Player/Player.h"
#include "BossMonsterMagicPatternC.h"

BossMonsterMagicPatternB::BossMonsterMagicPatternB() 
	: FrameCount_(0)
	, MagicEffectTime_(0)
	, MagicSetFlag_(false)
	, MagicEffectFlag_(false)
	, MagicEffectDrawFlag_(false)
	, Position_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, Damegecheck_(false)
	, GetDamegeFlag_(false)
{
}

BossMonsterMagicPatternB::~BossMonsterMagicPatternB()
{
	SceneGame::GetBossMagicB_1Efk()->SetIsDrawing(false);
}

void BossMonsterMagicPatternB::Update(BossMonster * _bossmonster)
{
	if (!MagicSetFlag_)
	{
		Damegecheck_ = false;
		_bossmonster->GetSkinMesh()->MyChangeAnim(31.0);
		MagicSetFlag_ = true;
	}
	if (FrameCount_ < 400)
	{
		if (FrameCount_ == 350)
		{
			MagicEffectFlag_ = true;
		}

		FrameCount_++;
	}
	else
	{
		_bossmonster->GetSkinMesh()->MyChangeAnim(63.3);
		FrameCount_ = 0;
		MagicSetFlag_ = false;
		_bossmonster->SetMagicCoolTime(0);
	}

	if (MagicEffectFlag_)
	{
		SceneGame::GetBossMagicB_1Efk()->SetScale(D3DXVECTOR3(20.0f, 20.0f, 20.0f));
		Position_ = SceneGame::GetPlayer()->GetOldPosition();
		SceneGame::GetBossMagicB_1Efk()->SetPosition(Position_);
		SceneGame::GetBossMagicB_1Efk()->SetIsDrawing(true);
		SceneGame::GetBossMagicB_1Efk()->SetFrameCount(0.5f);
		MagicEffectDrawFlag_ = true;
		GetDamegeFlag_ = true;
		MagicEffectFlag_ = false;
	}

	if (MagicEffectDrawFlag_)
	{
		if (GetDamegeFlag_)
		{
			spherecolision_.colision01.modelpos = Position_;
			spherecolision_.colision01.r = 1.0f;
			spherecolision_.colision02.modelpos = D3DXVECTOR3(Player::GetPlayerPosMatrix()._41, Player::GetPlayerPosMatrix()._42, Player::GetPlayerPosMatrix()._43);
			spherecolision_.colision02.r = 1.0f;
			Damegecheck_ = colision_.Collision_detection_of_Sphere_and_Sphere(spherecolision_);
			if (Damegecheck_)
			{
				SceneGame::GetPlayer()->Damage(300.0f);
			}
			else
			{
				SceneGame::GetPlayer()->Damage(0.0f);
			}

			GetDamegeFlag_ = false;
		}
		if (MagicEffectTime_ > 40)
		{
			SceneGame::GetBossMagicB_1Efk()->SetIsDrawing(false);
			MagicEffectTime_ = 0;
			MagicEffectDrawFlag_ = false;
		}
		MagicEffectTime_++;
	}

	if (_bossmonster->GetLife() < _bossmonster->GetMaxLife() * 0.5f)
	{
		_bossmonster->ChangeBossMonsterMagicPattern(new BossMonsterMagicPatternC);
	}
}
