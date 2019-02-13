#include "BossMonsterMagicPatternA.h"
#include "../BossMonster.h"
#include "../../MyEffekseer/MyEffekseer.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../Player/Player.h"
#include "BossMonsterMagicPatternB.h"
BossMonsterMagicPatternA::BossMonsterMagicPatternA()
	: FrameCount_(0)
	, MagicSetFlag_(false)
	, MagicEffectDrawFlag_(false)
	, Position_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, Damegecheck_(false)
	, GetDamegeFlag_(false)
	, ColisionCheck_(false)
{

}

BossMonsterMagicPatternA::~BossMonsterMagicPatternA()
{
	SceneGame::GetBossMagicAEfk()->SetIsDrawing(false);
}

void BossMonsterMagicPatternA::Update(BossMonster * _bossmonster)
{
	if (!MagicSetFlag_)
	{
		Damegecheck_ = false;
		_bossmonster->GetSkinMesh()->MyChangeAnim(26.7);
		MagicSetFlag_ = true;
	}
	if (FrameCount_ < 173)
	{
		FrameCount_++;
		if (FrameCount_ == 140)
		{
			_bossmonster->SetMagicPositionFlag(true);
		}
		if (FrameCount_ > 150)
		{
			if (FrameCount_ == 160)
			{
				MagicEffectDrawFlag_ = true;
				GetDamegeFlag_ = true;
				Damegecheck_ = true;
			}
			SceneGame::GetBossMagicAEfk()->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
			SceneGame::GetBossMagicAEfk()->SetIsDrawing(true);
			Position_ = SceneGame::GetPlayer()->GetOldPosition();
			SceneGame::GetBossMagicAEfk()->SetPosition(Position_);
			SceneGame::GetBossMagicAEfk()->SetFrameCount(1.0f);
		}
	}
	else
	{
		SceneGame::GetBossMagicAEfk()->SetIsDrawing(false);
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
			spherecolision_.colision01.r = 0.8f;
			spherecolision_.colision02.modelpos = D3DXVECTOR3(Player::GetPlayerPosMatrix()._41, Player::GetPlayerPosMatrix()._42, Player::GetPlayerPosMatrix()._43);
			spherecolision_.colision02.r = 0.8f;
			ColisionCheck_ = colision_.Collision_detection_of_Sphere_and_Sphere(spherecolision_);
			if (ColisionCheck_ && Damegecheck_)
			{
				D3DXVECTOR3 knockbackpos = SceneGame::GetPlayer()->GetPlayerPosition() - _bossmonster->Position();
				SceneGame::GetPlayer()->Damage(150.0f, knockbackpos);
				Damegecheck_ = false;
				GetDamegeFlag_ = false;
			}
			else if(!ColisionCheck_ && Damegecheck_)
			{
				SceneGame::GetPlayer()->Damage(0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				Damegecheck_ = false;
				GetDamegeFlag_ = false;
			}
		}
		else
		{
			MagicEffectDrawFlag_ = false;
		}
	}

	if (_bossmonster->GetLife() < _bossmonster->GetMaxLife() * 0.75f)
	{
		_bossmonster->ChangeBossMonsterMagicPattern(new BossMonsterMagicPatternB);
	}
}
