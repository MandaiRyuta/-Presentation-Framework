#include "SceneGame.h"
#include "../../main.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../System/InheritanceNode/MeshFiled.h"
#include "../../System/InheritanceNode/Skydome.h"
#include "../../System/InheritanceNode/Instancing3D.h"
#include "../../System/InheritanceNode/Player/Player.h"
#include "../../System/InheritanceNode/Sea.h"
#include "../../System/InheritanceNode/MotionEffect/MotionEffect.h"
#include "../../System/InheritanceNode/BossMonster/BossMonster.h"
#include "../../Shadow/StenshilShadow.h"
#include "../../System/Polygon2D.h"
#include "../../System/colision/SphereColision.h"
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
#include "../../LoadManager/TextureLoder.h"
#include "../../System/InheritanceNode/MagicObject/MagicObject.h"

MeshFiled* SceneGame::meshfiled_;
MyEffekseer* SceneGame::PlayerMagicEfk_ = nullptr;
MyEffekseer* SceneGame::PlayerAttack01Efk_ = nullptr;
MyEffekseer* SceneGame::PlayerAttack02Efk_ = nullptr;
MyEffekseer* SceneGame::PlayerAttack03Efk_ = nullptr;
MyEffekseer* SceneGame::PlayerBuffEfk_ = nullptr;
MyEffekseer* SceneGame::EnemyBuff01Efk_ = nullptr;
MyEffekseer* SceneGame::EnemyBuff02Efk_ = nullptr;
Polygon2D* SceneGame::HealthBar_ = nullptr;
Polygon2D* SceneGame::ManaBar_ = nullptr;
void SceneGame::Initialize()
{
	Entity::MeshFiledSize filedsize;
	
	filedsize.filed_x = MeshFiledX;
	filedsize.filed_z = MeshFiledZ;
	filedsize.size_x = MeshFiledXSize;
	filedsize.size_z = MeshFiledZSize;
	
	meshfiled_ = MeshFiled::Create(filedsize);

	Skydome::Create();

	StenshilShadow::Create(0);
	StenshilShadow::Create(1);
	PlayerMagicEfk_ =MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/MagicArea.efk");
	PlayerAttack01Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/Attack01.efk");
	PlayerAttack02Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/Attack02.efk");
	PlayerAttack03Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/Attack03.efk");
	PlayerBuffEfk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/Buff01.efk");
	EnemyBuff01Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/EnemyBuff.efk");
	EnemyBuff02Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/EnemyBuff.efk");
	Polygon2D::Create(1, 5.0f, 240.0f, 550.0f, 250.0f, 0, 0, 2000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(STATUS));
	HealthBar_ = Polygon2D::Create(1, 132.0f, 280.0f, 250.0f, 55.0f, 0, 0, 2000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(HP));
	ManaBar_ = Polygon2D::Create(1, 132.0f, 300.0f, 250.0f, 55.0f, 0, 0, 2000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(MANA));
	Polygon2D::Create(0, 0.0f, 0.0f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, windows_rect::SCREEN_WIDTH, windows_rect::SCREEN_HEIGHT, D3DCOLOR_RGBA(0, 0, 0, 155),true,0.0f,0.0f,0.0f,NULL);
	Player::Create();
	BossMonster::Create(500, 1000);
	//Instancing3D::Create();
	Sea::Create();

	MosionEffect::CreateMotionEffect(1);
	MagicObject::Create(1);

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

MyEffekseer * SceneGame::GetPlayerMagicEfk()
{
	return PlayerMagicEfk_;
}

MyEffekseer * SceneGame::GetPlayerAttack01Efk()
{
	return PlayerAttack01Efk_;
}

MyEffekseer * SceneGame::GetPlayerAttack02Efk()
{
	return PlayerAttack02Efk_;
}

MyEffekseer * SceneGame::GetPlayerAttack03Efk()
{
	return PlayerAttack03Efk_;
}

MyEffekseer * SceneGame::GetPlayerBuffEfk()
{
	return PlayerBuffEfk_;
}

MyEffekseer * SceneGame::GetEnemyBuf01Efk()
{
	return EnemyBuff01Efk_;
}

MyEffekseer * SceneGame::GetEnemyBuf02Efk()
{
	return EnemyBuff02Efk_;
}

MeshFiled * SceneGame::GetMeshFiled()
{
	return meshfiled_;
}

Polygon2D * SceneGame::GetHealthBar()
{
	return HealthBar_;
}

Polygon2D * SceneGame::GetManaBar()
{
	return ManaBar_;
}
