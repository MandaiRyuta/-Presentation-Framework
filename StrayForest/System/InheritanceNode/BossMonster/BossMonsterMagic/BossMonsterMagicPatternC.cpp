#include "BossMonsterMagicPatternC.h"
#include "../BossMonster.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MyEffekseer/MyEffekseer.h"

BossMonsterMagicPatternC::BossMonsterMagicPatternC() 
	: FrameCount_(0)
	, MagicEffectDrawFlag_(false)
	, Position_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, Damegecheck_(false)
	, GetDamegeFlag_(false)
	, ColisionCheck_(false)
{
}

BossMonsterMagicPatternC::~BossMonsterMagicPatternC()
{
	SceneGame::GetBossMagicCEfk()->SetIsDrawing(false);
}

void BossMonsterMagicPatternC::Update(BossMonster * _bossmonster)
{
	if (!_bossmonster->GetMagicState())
	{
		Damegecheck_ = false;
		_bossmonster->GetSkinMesh()->MyChangeAnim(37.0);
		_bossmonster->SetMagicState(true);
	}

	if (FrameCount_ < 140)
	{
		FrameCount_++;
		if (FrameCount_ == 110)
		{
			_bossmonster->SetMagicPositionFlag(true);
		}
		if (FrameCount_ > 120)
		{
			if (FrameCount_ == 130)
			{
				MagicEffectDrawFlag_ = true;
				GetDamegeFlag_ = true;
				Damegecheck_ = true;
			}
			SceneGame::GetBossMagicCEfk()->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
			SceneGame::GetBossMagicCEfk()->SetIsDrawing(true);
			Position_ = SceneGame::GetPlayer()->GetOldPosition();
			Position_.y = Position_.y + 15.0f;
			SceneGame::GetBossMagicCEfk()->SetPosition(Position_);
			SceneGame::GetBossMagicCEfk()->SetFrameCount(1.0f);
		}
	}
	else
	{
		SceneGame::GetBossMagicCEfk()->SetIsDrawing(false);
		_bossmonster->SetMagicCoolTime(0);
		_bossmonster->GetSkinMesh()->MyChangeAnim(63.3);
		FrameCount_ = 0;
		_bossmonster->SetMagicState(false);
	}


	if (MagicEffectDrawFlag_)
	{
		if (GetDamegeFlag_)
		{
			spherecolision_.colision01.modelpos = Position_;
			spherecolision_.colision01.r = 1.3f;
			spherecolision_.colision02.modelpos = D3DXVECTOR3(Player::GetPlayerPosMatrix()._41, Player::GetPlayerPosMatrix()._42, Player::GetPlayerPosMatrix()._43);
			spherecolision_.colision02.r = 1.3f;
			ColisionCheck_ = colision_.Collision_detection_of_Sphere_and_Sphere(spherecolision_);
			D3DXVECTOR3 knockbackpos = SceneGame::GetPlayer()->GetPlayerPosition() - _bossmonster->Position();
			if (ColisionCheck_ && Damegecheck_)
			{
				SceneGame::GetPlayer()->Damage(450.0f, knockbackpos);
				Damegecheck_ = false;
				GetDamegeFlag_ = false;
			}
			else if(!ColisionCheck_ && Damegecheck_)
			{
				SceneGame::GetPlayer()->Damage(0.0f, knockbackpos);
				Damegecheck_ = false;
				GetDamegeFlag_ = false;
			}
		}
		else
		{
			MagicEffectDrawFlag_ = false;
		}
	}
}
