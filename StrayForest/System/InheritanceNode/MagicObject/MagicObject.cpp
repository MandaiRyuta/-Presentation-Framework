#include "MagicObject.h"
#include <stdio.h>

#include "../Player/Player.h"
#include "../BossMonster/BossMonster.h"

#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../BossMonster/BossMonster.h"
#include "../../../SceneManager/InheritanceNode/SceneChutorial.h"
#include "../../../Renderer/GameManager.h"
#include "../BossMonster/ChutorialBoss.h"

Entity::MAGIC_WORK MagicObject::magic[MAGIC_NUM] = {};
D3DXVECTOR3 MagicObject::TargetVec_[MAGIC_NUM] = {};
D3DXVECTOR3 MagicObject::OwnerVec_[MAGIC_NUM] = {};
D3DXVECTOR3 MagicObject::target_;
D3DXVECTOR3 MagicObject::pos_;

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
}

MagicObject::~MagicObject()
{
}

void MagicObject::Init()
{
}
float count = 0.0f;
void MagicObject::Update()
{
	ImGui::GetPositionInfomation("Position", magic[0].position);

	for (int i = 0; i < MAGIC_NUM; i++)
	{
		if (magic[i].IsDraw)
		{
			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				SceneChutorial::GetMagicObject(i)->SetIsDrawing(true);
			}
			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				SceneGame::GetMagicObjects(i)->SetIsDrawing(true);
			}
			if (magic[i].frame >= 0.3f)
			{
				if (i < 9)
				{
					magic[i + 1].IsDraw = true;
				}
			}
			if (magic[i].frame >= 1.0f)
			{
				magic[i].IsDraw = false;
			}
			D3DXVec3Hermite(&magic[i].position, &pos_, &OwnerVec_[i], &target_, &TargetVec_[i], magic[i].frame);
			
			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				switch (i)
				{
				case 0:
					SceneChutorial::GetMagicObject(0)->SetPosition(magic[0].position);
					break;
				case 1:
					SceneChutorial::GetMagicObject(1)->SetPosition(magic[1].position);
					break;
				case 2:
					SceneChutorial::GetMagicObject(2)->SetPosition(magic[2].position);
					break;
				case 3:
					SceneChutorial::GetMagicObject(3)->SetPosition(magic[3].position);
					break;
				case 4:
					SceneChutorial::GetMagicObject(4)->SetPosition(magic[4].position);
					break;
				case 5:
					SceneChutorial::GetMagicObject(5)->SetPosition(magic[5].position);
					break;
				case 6:
					SceneChutorial::GetMagicObject(6)->SetPosition(magic[6].position);
					break;
				case 7:
					SceneChutorial::GetMagicObject(7)->SetPosition(magic[7].position);
					break;
				case 8:
					SceneChutorial::GetMagicObject(8)->SetPosition(magic[8].position);
					break;
				case 9:
					SceneChutorial::GetMagicObject(9)->SetPosition(magic[9].position);
					break;
				default:
					break;
				}
			}
			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				switch (i)
				{
				case 0:
					SceneGame::GetMagicObjects(0)->SetPosition(magic[0].position);
					break;
				case 1:
					SceneGame::GetMagicObjects(1)->SetPosition(magic[1].position);
					break;
				case 2:
					SceneGame::GetMagicObjects(2)->SetPosition(magic[2].position);
					break;
				case 3:
					SceneGame::GetMagicObjects(3)->SetPosition(magic[3].position);
					break;
				case 4:
					SceneGame::GetMagicObjects(4)->SetPosition(magic[4].position);
					break;
				case 5:
					SceneGame::GetMagicObjects(5)->SetPosition(magic[5].position);
					break;
				case 6:
					SceneGame::GetMagicObjects(6)->SetPosition(magic[6].position);
					break;
				case 7:
					SceneGame::GetMagicObjects(7)->SetPosition(magic[7].position);
					break;
				case 8:
					SceneGame::GetMagicObjects(8)->SetPosition(magic[8].position);
					break;
				case 9:
					SceneGame::GetMagicObjects(9)->SetPosition(magic[9].position);
					break;
				default:
					break;
				}
			}
			magic[i].frame += 0.05f;
		}
		else
		{
			magic[i].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				SceneChutorial::GetMagicObject(i)->SetIsDrawing(false);
			}
			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				SceneGame::GetMagicObjects(i)->SetIsDrawing(false);
			}
		}

		if (magic[9].IsDraw)
		{
			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				SceneChutorial::GetExplosion()->SetIsDrawing(true);
				SceneChutorial::GetExplosion()->SetFrameCount(1.0f);
				SceneChutorial::GetExplosion()->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
				SceneChutorial::GetExplosion()->SetPosition(SceneChutorial::GetChutorialBoss()->GetPosition());
			}
			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				SceneGame::GetHitExplosion()->SetIsDrawing(true);
				SceneGame::GetHitExplosion()->SetFrameCount(1.0f);
				SceneGame::GetHitExplosion()->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
				SceneGame::GetHitExplosion()->SetPosition(SceneGame::GetBossMonster()->GetPosition());
			}
			count+= 0.1f;
		}
		if (count > 5.0f)
		{
			if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
			{
				SceneChutorial::GetExplosion()->SetIsDrawing(false);
				SceneChutorial::GetExplosion()->StopEffect();
			}
			if (GameManager::GetSceneNumber() == SCENE_GAME)
			{
				SceneGame::GetBossMonster()->Damage(50);
				SceneGame::GetHitExplosion()->SetIsDrawing(false);
				SceneGame::GetHitExplosion()->StopEffect();
			}
			count = 0.0f;
		}
	}
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

void MagicObject::MoveMagic()
{
}

void MagicObject::StartMagic(D3DXVECTOR3 target, D3DXVECTOR3 pos)
{
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
		magic[i].IsDraw = false;
		OwnerVec_[i] = pos + D3DXVECTOR3(Hermite[i].x, Hermite[i].y, 100.0f);
		TargetVec_[i] = target - D3DXVECTOR3(Hermite[i].x, Hermite[i].y, 100.0f);
		time += 0.1f;
	}

	magic[0].IsDraw = true;
}
