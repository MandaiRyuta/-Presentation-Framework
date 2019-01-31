#include "SceneChutorial.h"
#include "../../System/InheritanceNode/Player/ChutorialPlayer.h"
#include "../../System/InheritanceNode/MeshFiled.h"
#include "../../System/InheritanceNode/Skydome.h"
#include "../../System/InheritanceNode/Sea.h"
#include "../../System/Polygon2D.h"
#include "../../System/Polygon3D.h"
#include "../../System/InheritanceNode/BossMonster/ChutorialBoss.h"
#include "../../System/InheritanceNode/Player/PlayerItem/PlayerShiled.h"
#include "../../System/InheritanceNode/Player/PlayerItem/PlayerWeapon.h"
#include "../../System/InheritanceNode/MagicObject/MagicObject.h"
#include "../../System/Polygon2D.h"
#include "../../LoadManager/TextureLoder.h"
MeshFiled* SceneChutorial::meshfiled_ = nullptr;
Sword* SceneChutorial::sword_ = nullptr;
Shiled* SceneChutorial::shiled_ = nullptr;
ChutorialPlayer* SceneChutorial::chutorialplayer_ = nullptr;
ChutorialBoss* SceneChutorial::chutorialboss_ = nullptr;
MyEffekseer* SceneChutorial::ChutorialHitExplosion_ = nullptr;
MyEffekseer* SceneChutorial::ChutorialMagicObjects[10] = {};
MyEffekseer* SceneChutorial::ChutorialPlayerAttack01Efk_ = nullptr;
MyEffekseer* SceneChutorial::ChutorialPlayerMagicEfk_ = nullptr;
Polygon2D* SceneChutorial::LeftController_ = nullptr;
Polygon2D* SceneChutorial::RightController_ = nullptr;
Sword* SceneChutorial::chutorialsword_ = nullptr;
Shiled* SceneChutorial::chutorialshiled_ = nullptr;
void SceneChutorial::Initialize()
{
	Skydome::Create();

	Entity::MeshFiledSize filedsize;

	filedsize.filed_x = MeshFiledX;
	filedsize.filed_z = MeshFiledZ;
	filedsize.size_x = MeshFiledXSize;
	filedsize.size_z = MeshFiledZSize;
	meshfiled_ = MeshFiled::Create(filedsize);
	Sea::Create();
	chutorialplayer_ = ChutorialPlayer::Create();
	chutorialboss_ = ChutorialBoss::Create();
	for (int i = 0; i < 10; i++)
	{
		ChutorialMagicObjects[i] = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/magicobjects.efk");
	}
	ChutorialPlayerMagicEfk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/MagicArea.efk");
	ChutorialPlayerAttack01Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/Attack01.efk");
	ChutorialHitExplosion_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/HitExplosion.efk");
	Polygon2D::Create(1, 10.0f, 360.0f, 300.0f, 100.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(CONTROLBUTTON02),true);
	LeftController_ = Polygon2D::Create(1, 22.5f, 360.0f, 250.0f, 80.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(CONTROLBUTTON01), true);

	Polygon2D::Create(1, (windows_rect::SCREEN_WIDTH * 0.5f) + 50.0f, windows_rect::SCREEN_HEIGHT - 150.0f, 300.0f, 100.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(CONTROLBUTTON02), true);
	RightController_ = Polygon2D::Create(1, (windows_rect::SCREEN_WIDTH * 0.5f) + 62.5f, windows_rect::SCREEN_HEIGHT - 150.0f, 250.0f,  80.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(CONTROLBUTTON01), true);
	
	Polygon2D::Create(1, (windows_rect::SCREEN_WIDTH * 0.5f) - 125.0f, windows_rect::SCREEN_HEIGHT - 150.0f, 120.0f, 40.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(155, 155, 155, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(CONTROLBUTTON01), true);

	Polygon2D::Create(1, 80.0f, 100.0f, 450.0f, 120.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(SIDEBUTTON), true);
	Polygon2D::Create(1, windows_rect::SCREEN_WIDTH - 300.0f, 100.0f, 450.0f, 120.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f,0.0f,0.0f, TextureLoder::GetTextureData(SIDEBUTTON), true);
	Polygon2D::Create(1, windows_rect::SCREEN_WIDTH - 230.0f, 100.0f, 150.0f,  60.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(PLAYERRUN), true);

	Polygon2D::Create(1, 1100.0f, 325.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(XBUTTON), true);
	Polygon2D::Create(1, 1200.0f, 325.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(BBUTTON), true);
	Polygon2D::Create(1, 1150.0f, 250.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(YBUTTON), true);
	Polygon2D::Create(1, 1150.0f, 425.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ABUTTON), true);
	Polygon2D::Create(1, 1105.0f, 325.0f, 100.0f, 75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(MAGIC), true);
	Polygon2D::Create(1, 1205.0f, 325.0f, 100.0f, 75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ATTACK), true);
	Polygon2D::Create(1, 1152.5f, 250.0f, 100.0f, 75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(DEF), true);
	Polygon2D::Create(1, 1152.5f, 425.0f, 100.0f, 75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ROLL), true);
	
	chutorialsword_ = Sword::Create(0);
	chutorialshiled_ = Shiled::Create(0);
	MagicObject::Create(1);
}

void SceneChutorial::Update()
{
}

void SceneChutorial::Draw()
{
}

void SceneChutorial::Release()
{
}

MeshFiled * SceneChutorial::GetMeshFiled()
{
	return meshfiled_;
}

Sword * SceneChutorial::GetSword()
{
	return sword_;
}

Shiled * SceneChutorial::GetShiled()
{
	return shiled_;
}

ChutorialPlayer * SceneChutorial::GetChutorialPlayer()
{
	return chutorialplayer_;
}

ChutorialBoss * SceneChutorial::GetChutorialBoss()
{
	return chutorialboss_;
}

MyEffekseer * SceneChutorial::GetExplosion()
{
	return ChutorialHitExplosion_;
}

MyEffekseer * SceneChutorial::GetMagicObject(int num)
{
	return ChutorialMagicObjects[num];
}

MyEffekseer * SceneChutorial::GetPlayerMagicEfk()
{
	return ChutorialPlayerMagicEfk_;
}

MyEffekseer * SceneChutorial::GetPlayerAttackEfk()
{
	return ChutorialPlayerAttack01Efk_;
}

Polygon2D * SceneChutorial::GetLeftController()
{
	return LeftController_;
}

Polygon2D * SceneChutorial::GetRightController()
{
	return RightController_;
}

Sword * SceneChutorial::GetSwordModel()
{
	return chutorialsword_;
}

Shiled * SceneChutorial::GetShiledModel()
{
	return chutorialshiled_;
}


