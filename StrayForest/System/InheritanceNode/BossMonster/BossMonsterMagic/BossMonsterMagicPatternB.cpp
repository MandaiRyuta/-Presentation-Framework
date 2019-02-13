#include "BossMonsterMagicPatternB.h"
#include "../BossMonster.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MyEffekseer/MyEffekseer.h"
#include "../../Player/Player.h"
#include "BossMonsterMagicPatternC.h"

BossMonsterMagicPatternB::BossMonsterMagicPatternB() 
	: FrameCount_(0)
	, MagicSetFlag_(false)
	, MagicEffectDrawFlag_(false)
	, Position_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, Damegecheck_(false)
	, GetDamegeFlag_(false)
	, ColisionCheck_(false)
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
		_bossmonster->GetSkinMesh()->MyChangeAnim(31.0f);
		MagicSetFlag_ = true;
	}
	if (FrameCount_ < 200)
	{
		FrameCount_++;
		if (FrameCount_ == 90)
		{
			_bossmonster->SetMagicPositionFlag(true);
		}
		if (FrameCount_ > 100)
		{
			SceneGame::GetBossMagicB_1Efk()->SetScale(D3DXVECTOR3(20.0f, 20.0f, 20.0f));
			Position_ = SceneGame::GetPlayer()->GetOldPosition();
			SceneGame::GetBossMagicB_1Efk()->SetPosition(Position_);
			SceneGame::GetBossMagicB_1Efk()->SetIsDrawing(true);
			SceneGame::GetBossMagicB_1Efk()->SetFrameCount(1.0f);
		}
		if (FrameCount_ == 110)
		{
			MagicEffectDrawFlag_ = true;
			GetDamegeFlag_ = true;
			Damegecheck_ = true;
		}
		if (FrameCount_ > 120)
		{
			SceneGame::GetBossMagicB_1Efk()->SetIsDrawing(false);
		}
	}
	else
	{
		_bossmonster->SetMagicCoolTime(0);
		_bossmonster->GetSkinMesh()->MyChangeAnim(63.3);
		FrameCount_ = 0;
		MagicSetFlag_ = false;

	}

	if (MagicEffectDrawFlag_)
	{
		if (GetDamegeFlag_)
		{
			spherecolision_.colision01.modelpos = Position_;
			spherecolision_.colision01.r = 1.0f;
			spherecolision_.colision02.modelpos = D3DXVECTOR3(Player::GetPlayerPosMatrix()._41, Player::GetPlayerPosMatrix()._42, Player::GetPlayerPosMatrix()._43);
			spherecolision_.colision02.r = 1.0f;
			ColisionCheck_ = colision_.Collision_detection_of_Sphere_and_Sphere(spherecolision_);
			D3DXVECTOR3 knockbackpos = SceneGame::GetPlayer()->GetPlayerPosition() - _bossmonster->Position();
			if (ColisionCheck_ && Damegecheck_)
			{
				SceneGame::GetPlayer()->Damage(300.0f, knockbackpos);
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

	if (_bossmonster->GetLife() < _bossmonster->GetMaxLife() * 0.5f)
	{
		_bossmonster->ChangeBossMonsterMagicPattern(new BossMonsterMagicPatternC);
	}
}
