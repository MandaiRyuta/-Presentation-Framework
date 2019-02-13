#include "MagicObject.h"
#include <stdio.h>

#include "../Player/Player.h"
#include "../BossMonster/BossMonster.h"

#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../BossMonster/BossMonster.h"
#include "../../../SceneManager/InheritanceNode/SceneChutorial.h"
#include "../../../Renderer/GameManager.h"
#include "../BossMonster/ChutorialBoss.h"
#include "../MyEffekseer/MyEffekseer.h"

MagicObject::MagicObject(int _Priority) 
	: GameObjectManager(_Priority)
{
	if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
	{
		SceneChutorial::GetExplosion()->SetIsDrawing(false);
		SceneChutorial::GetExplosion()->SetFrameCount(0.1f);
	}
	if (GameManager::GetSceneNumber() == SCENE_GAME)
	{
		SceneGame::GetHitExplosion()->SetIsDrawing(false);
		SceneGame::GetHitExplosion()->SetFrameCount(0.1f);
	}

	for (int i = 0; i < MAGIC_NUM; i++)
	{
		magic[i].position = D3DXVECTOR3(0.0f,0.0f,0.0f);
		magic[i].IsDraw = false;
		magic[i].frame = 0.0f;
		if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
		{
			SceneChutorial::GetMagicObject(i)->SetIsDrawing(false);
			SceneChutorial::GetMagicObject(i)->SetFrameCount(0.1f);
		}
		if (GameManager::GetSceneNumber() == SCENE_GAME)
		{
			SceneGame::GetMagicObjects(i)->SetIsDrawing(false);
			SceneGame::GetMagicObjects(i)->SetFrameCount(0.1f);
		}
	}
	objectdrawflag_ = false;
	objectnum_ = 0;
	usetime_ = 0;
}

MagicObject::~MagicObject()
{
}

void MagicObject::Init()
{
	count_ = 0;
}
void MagicObject::Update()
{
	if (usetime_ > 25)
	{
		if (objectnum_ < 9)
		{
			for (int i = 0; i < MAGIC_NUM; i++)
			{
				if (magic[i].frame >= 1.0f)
				{
					if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
					{
						SceneChutorial::GetMagicObject(i)->SetIsDrawing(false);
					}
					if (GameManager::GetSceneNumber() == SCENE_GAME)
					{
						SceneGame::GetMagicObjects(i)->SetIsDrawing(false);
					}
				}
			}
		}

		if (magic[objectnum_].frame >= 0.3f)
		{
			if (objectnum_ < 9)
			{
				magic[objectnum_].IsDraw = true;
			}
		}

		if (magic[objectnum_].frame >= 1.0f)
		{
			magic[objectnum_].IsDraw = false;
			if (objectnum_ < 9)
			{
				objectnum_++;
			}
		}

		if (magic[objectnum_].IsDraw)
		{
			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				SceneChutorial::GetMagicObject(objectnum_)->SetIsDrawing(true);
			}

			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				SceneGame::GetMagicObjects(objectnum_)->SetIsDrawing(true);
			}

			D3DXVec3Hermite(&magic[objectnum_].position, &pos_, &OwnerVec_[objectnum_], &target_, &TargetVec_[objectnum_], magic[objectnum_].frame);

			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				SceneChutorial::GetMagicObject(objectnum_)->SetPosition(magic[objectnum_].position);
			}
			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				SceneGame::GetMagicObjects(objectnum_)->SetPosition(magic[objectnum_].position);
			}

			magic[objectnum_].frame += 0.15f;
		}
		else
		{
			magic[objectnum_].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				SceneChutorial::GetMagicObject(objectnum_)->SetIsDrawing(false);
			}
			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				SceneGame::GetMagicObjects(objectnum_)->SetIsDrawing(false);
			}
		}
	}

	if (magic[9].frame >= 1.0f)
	{
		if (magic[9].IsDraw)
		{
			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				SceneChutorial::GetExplosion()->SetIsDrawing(true);
				SceneChutorial::GetExplosion()->SetFrameCount(1.0f);
				SceneChutorial::GetExplosion()->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
				D3DXVECTOR3 HitEffectPos = D3DXVECTOR3(SceneChutorial::GetChutorialBoss()->GetPosition().x, SceneChutorial::GetChutorialBoss()->GetPosition().y + 50.0f, SceneChutorial::GetChutorialBoss()->GetPosition().z);
				SceneChutorial::GetExplosion()->SetPosition(HitEffectPos);
				objectdrawflag_ = true;
			}
			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				SceneGame::GetHitExplosion()->SetIsDrawing(true);
				SceneGame::GetHitExplosion()->SetFrameCount(1.0f);
				SceneGame::GetHitExplosion()->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
				D3DXVECTOR3 HitEffectPos = D3DXVECTOR3(SceneGame::GetBossMonster()->GetPosition().x, SceneGame::GetBossMonster()->GetPosition().y + 50.0f, SceneGame::GetBossMonster()->GetPosition().z);
				SceneGame::GetHitExplosion()->SetPosition(HitEffectPos);
				objectdrawflag_ = true;
			}
		}
	}

	if (objectdrawflag_)
	{
		count_++;
	}

	if (count_ > 120)
	{
		if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
		{
			SceneChutorial::GetExplosion()->SetIsDrawing(false);
			SceneChutorial::GetExplosion()->StopEffect();
			count_ = 0;
			objectdrawflag_ = false;
		}
		if (GameManager::GetSceneNumber() == SCENE_GAME)
		{
			D3DXVECTOR3 knockbackpos = SceneGame::GetBossMonster()->GetPosition() - SceneGame::GetPlayer()->GetPlayerPosition();
			SceneGame::GetBossMonster()->Damage(210.0f, knockbackpos);
			SceneGame::GetHitExplosion()->SetIsDrawing(false);
			SceneGame::GetHitExplosion()->StopEffect();
			count_ = 0;
			objectdrawflag_ = false;
		}
	}

	usetime_++;
}

void MagicObject::Draw()
{
}

void MagicObject::Uninit()
{
}

MagicObject * MagicObject::Create(int _Priority)
{
	MagicObject* magicobj = new MagicObject(_Priority);
	magicobj->Init();
	return magicobj;
}

void MagicObject::StartMagic(D3DXVECTOR3 target, D3DXVECTOR3 pos)
{
	usetime_ = 0;
	objectnum_ = 0;
	pos_ = pos;
	target_ = target;
	D3DXVECTOR3 startvec,endvec,startpos,endpos;
	D3DXVECTOR3 Hermite[MAGIC_NUM] = {};

	startpos = pos_ + D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	startvec = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	endpos = pos_ + D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	endvec = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	float time = 0.0f;

	for (int i = 0; i < MAGIC_NUM; i++)
	{
		if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
		{
			SceneChutorial::GetMagicObject(i)->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		}
		if (GameManager::GetSceneNumber() == SCENE_GAME)
		{
			SceneGame::GetMagicObjects(i)->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
		}
		D3DXVec3Hermite(&Hermite[i], &startpos, &startvec, &endpos, &endvec, time);
		magic[i].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		magic[i].frame = 0.0f;
		magic[i].IsDraw = true;
		OwnerVec_[i] = pos + D3DXVECTOR3(Hermite[i].x, Hermite[i].y, 100.0f);
		TargetVec_[i] = target - D3DXVECTOR3(Hermite[i].x, Hermite[i].y, 100.0f);
		time += 0.1f;
	}
}
