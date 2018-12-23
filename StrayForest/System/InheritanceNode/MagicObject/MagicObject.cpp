#include "MagicObject.h"
#include <stdio.h>

#include "../Player/Player.h"
#include "../BossMonster/BossMonster.h"

#include "../../../SceneManager/InheritanceNode/SceneGame.h"

Entity::MAGIC_WORK MagicObject::magic[MAGIC_NUM] = {};
D3DXVECTOR3 MagicObject::TargetVec_;
D3DXVECTOR3 MagicObject::OwnerVec_;
D3DXVECTOR3 MagicObject::target_;
D3DXVECTOR3 MagicObject::pos_;
D3DXVECTOR3 MagicObject::MovePos[100];
bool MagicObject::flag_;
MagicObject::MagicObject(int _Priority) 
	: GameObjectManager(_Priority)
	, IsDraw_(false)
{
	dir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < MAGIC_NUM; i++)
	{
		magic[i].bUse = true;
		magic[i].bDead = false;
		magic[i].position = D3DXVECTOR3(Player::GetPlayerPosMatrix()._41, Player::GetPlayerPosMatrix()._42, Player::GetPlayerPosMatrix()._43);
		///
		magic[i].time = 360;
		
	}
	flag_ = false;
	SceneGame::GetPlayerMagicEfk()->SetIsDrawing(true);
}

MagicObject::~MagicObject()
{
}

void MagicObject::Init()
{
}
static float frame = 0.0f;
void MagicObject::Update()
{
	ImGui::GetPositionInfomation("Position", magic[0].position);
	if (flag_)
	{
		if (frame >= 1.0f)
		{
			flag_ = false;
		}
		D3DXVec3Hermite(&magic[0].position, &pos_, &OwnerVec_, &target_, &TargetVec_, frame);
		SceneGame::GetPlayerMagicEfk()->SetPosition(magic[0].position);

		frame+= 0.1f;
	}
	else
	{
		magic[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		frame = 0.0f;
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
	frame = 0;
	flag_ = true;
	pos_ = pos;
	target_ = target;
	OwnerVec_ = pos + D3DXVECTOR3(0.0f, 100.0f, 100.0f);

	TargetVec_ = target + D3DXVECTOR3(0.0f, -100.0f, 100.0f);

}
