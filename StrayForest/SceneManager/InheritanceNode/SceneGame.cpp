#include "SceneGame.h"
#include "../../main.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../System/InheritanceNode/MeshFiled.h"
#include "../../System/InheritanceNode/Skydome.h"
#include "../../System/InheritanceNode/Instancing3D.h"
#include "../../System/InheritanceNode/Player/Player.h"
#include "../../System/InheritanceNode/Sea.h"
#include "../../System/MotionEffect.h"
#include "../../System/InheritanceNode/Guardian/Guardian.h"
#include "../../System/InheritanceNode/BossMonster/BossMonster.h"
#include "../../Shadow/StenshilShadow.h"
#include "../../System/Polygon2D.h"
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
MeshFiled* SceneGame::meshfiled_;

void SceneGame::Initialize()
{
	Entity::MeshFiledSize filedsize;
	
	filedsize.filed_x = MeshFiledX;
	filedsize.filed_z = MeshFiledZ;
	filedsize.size_x = MeshFiledXSize;
	filedsize.size_z = MeshFiledZSize;
	MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/MagicArea.efk");
	meshfiled_ = MeshFiled::Create(filedsize);
	Skydome::Create();
	StenshilShadow::Create(0);
	StenshilShadow::Create(1);
	Polygon2D::Create(0, 0.0f, 0.0f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, windows_rect::SCREEN_WIDTH, windows_rect::SCREEN_HEIGHT, D3DCOLOR_RGBA(0, 0, 0, 155),true,0.0f,0.0f,0.0f,NULL);
	Player::Create();
	BossMonster::Create(500, 1000);
	//Instancing3D::Create();
	Sea::Create();
	MeshEffect::Create();
	//Guardian::Create();
}

void SceneGame::Update()
{
}

void SceneGame::Draw()
{
}

void SceneGame::Release()
{
	GameObjectManager::ReleaseAll();
}

MeshFiled * SceneGame::GetMeshFiled()
{
	return meshfiled_;
}
