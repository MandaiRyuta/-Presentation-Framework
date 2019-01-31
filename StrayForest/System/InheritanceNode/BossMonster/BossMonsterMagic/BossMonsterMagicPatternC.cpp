#include "BossMonsterMagicPatternC.h"
#include "../BossMonster.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MyEffekseer/MyEffekseer.h"

BossMonsterMagicPatternC::BossMonsterMagicPatternC() 
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

BossMonsterMagicPatternC::~BossMonsterMagicPatternC()
{
	SceneGame::GetBossMagicCEfk()->SetIsDrawing(false);
}

void BossMonsterMagicPatternC::Update(BossMonster * _bossmonster)
{
	if (!MagicSetFlag_)
	{
		Damegecheck_ = false;
		_bossmonster->GetSkinMesh()->MyChangeAnim(37.0);
		MagicSetFlag_ = true;
	}

	if (FrameCount_ < 280)
	{
		if (FrameCount_ == 230)
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
		SceneGame::GetBossMagicCEfk()->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
		SceneGame::GetBossMagicCEfk()->SetIsDrawing(true);
		Position_ = SceneGame::GetPlayer()->GetOldPosition();
		SceneGame::GetBossMagicCEfk()->SetPosition(Position_);
		SceneGame::GetBossMagicCEfk()->SetFrameCount(0.2f);
		MagicEffectDrawFlag_ = true;
		GetDamegeFlag_ = true;
		MagicEffectFlag_ = false;
	}

	if (MagicEffectDrawFlag_)
	{
		if (GetDamegeFlag_)
		{
			spherecolision_.colision01.modelpos = Position_;
			spherecolision_.colision01.r = 1.3f;
			spherecolision_.colision02.modelpos = D3DXVECTOR3(Player::GetPlayerPosMatrix()._41, Player::GetPlayerPosMatrix()._42, Player::GetPlayerPosMatrix()._43);
			spherecolision_.colision02.r = 1.3f;
			Damegecheck_ = colision_.Collision_detection_of_Sphere_and_Sphere(spherecolision_);
			if (Damegecheck_)
			{
				SceneGame::GetPlayer()->Damage(450.0f);
			}
			else
			{
				SceneGame::GetPlayer()->Damage(0.0f);
			}

			GetDamegeFlag_ = false;
		}

		if (MagicEffectTime_ > 120)
		{
			SceneGame::GetBossMagicCEfk()->SetIsDrawing(false);
			MagicEffectTime_ = 0;
			MagicEffectDrawFlag_ = false;
		}
		MagicEffectTime_++;
	}
}
