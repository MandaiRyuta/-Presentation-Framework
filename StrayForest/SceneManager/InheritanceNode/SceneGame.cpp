#include "SceneGame.h"
#include "../../main.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../System/InheritanceNode/MeshFiled.h"
#include "../../System/InheritanceNode/Skydome.h"
#include "../../System/InheritanceNode/Instancing3D.h"
#include "../../System/InheritanceNode/Sea.h"
#include "../../System/InheritanceNode/MotionEffect/MotionEffect.h"
#include "../../Shadow/StenshilShadow.h"
#include "../../System/Polygon2D.h"
#include "../../System/colision/SphereColision.h"
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
#include "../../LoadManager/TextureLoder.h"
#include "../../System/InheritanceNode/MagicObject/MagicObject.h"
#include "../../System/InheritanceNode/Player/PlayerItem/PlayerShiled.h"
#include "../../System/InheritanceNode/Player/PlayerItem/PlayerWeapon.h"
#include "../../../Renderer/GameManager.h"
#include "../../../InputManager/input.h"
MeshFiled* SceneGame::meshfiled_;
MyEffekseer* SceneGame::PlayerMagicEfk_ = nullptr;
MyEffekseer* SceneGame::PlayerAttack01Efk_ = nullptr;
MyEffekseer* SceneGame::EnemyBuff01Efk_ = nullptr;
MyEffekseer* SceneGame::EnemyBuff02Efk_ = nullptr;
MyEffekseer* SceneGame::MagicObjects[10] = {};
MyEffekseer* SceneGame::HitExplosion_ = nullptr;
MyEffekseer* SceneGame::BossMonsterMagicAEfk_ = nullptr;
MyEffekseer* SceneGame::BossMonsterMagicB_1Efk_ = nullptr;
MyEffekseer* SceneGame::BossMonsterMagicCEfk_ = nullptr;
MyEffekseer* SceneGame::BossMonsterBuffEfk_ = nullptr;
MyEffekseer* SceneGame::GetDamegeEffectONEfk_ = nullptr;
MyEffekseer* SceneGame::BossMonsterBuff2Efk_ = nullptr;
Polygon2D* SceneGame::HealthBar_ = nullptr;
Polygon2D* SceneGame::ManaBar_ = nullptr;
Polygon2D* SceneGame::DamegeEffect_ = nullptr;
MosionEffect* SceneGame::motioneffect_ = nullptr;
BossMonster* SceneGame::boss_ = nullptr;
Player* SceneGame::player_ = nullptr;
Sword* SceneGame::sword_ = nullptr;
Shiled* SceneGame::shiled_ = nullptr;
Polygon2D* SceneGame::PauseScreen_ = nullptr;
Polygon2D* SceneGame::PauseButtonOn01_ = nullptr;
Polygon2D* SceneGame::PauseButtonOn02_ = nullptr;
Polygon2D* SceneGame::PauseButtonOff01_ = nullptr;
Polygon2D* SceneGame::PauseButtonOff02_ = nullptr;

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
	EnemyBuff01Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/EnemyBuff.efk");
	EnemyBuff02Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/EnemyBuff.efk");
	HitExplosion_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/HitExplosion.efk");
	BossMonsterMagicAEfk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/BossMonsterMagicA.efk");
	BossMonsterMagicB_1Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/BossMonsterMagicB_1.efk");
	BossMonsterMagicCEfk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/BossMonsterMagicC_1.efk");
	BossMonsterBuffEfk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/BossMonsterBuff.efk");
	BossMonsterBuff2Efk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/BossEffectBuff.efk");
	GetDamegeEffectONEfk_ = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/DamegeEffectON.efk");
	for (int i = 0; i < 10; i++)
	{
		MagicObjects[i] = MyEffekseer::CreateMyEffect(1, L"Resource/EffekseerAsset/magicobjects.efk");
	}
	Polygon2D::Create(1, 5.0f, 240.0f, 550.0f, 250.0f, 0, 0, 2000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(STATUS),true);
	Polygon2D::Create(1, 135.0f, 287.5f, 240.0f, 27.5f, 0, 0, 2000, 1000, D3DCOLOR_RGBA(0, 0, 0, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(HP),true);
	Polygon2D::Create(1, 135.0f, 307.5f, 240.0f, 27.5f, 0, 0, 2000, 1000, D3DCOLOR_RGBA(0, 0, 0, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(HP),true);
	HealthBar_ = Polygon2D::Create(1, 135.0f, 287.5f, 240.0f, 27.5f, 0, 0, 2000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(HP),true);
	ManaBar_ = Polygon2D::Create(1, 135.0f, 307.5f, 240.0f, 27.5f, 0, 0, 2000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(MANA),true);
	Polygon2D::Create(0, 0.0f, 0.0f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, windows_rect::SCREEN_WIDTH, windows_rect::SCREEN_HEIGHT, D3DCOLOR_RGBA(0, 0, 0, 155),true,0.0f,0.0f,0.0f,NULL,true);
	DamegeEffect_ = Polygon2D::Create(1, 0.0f, 0.0f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, windows_rect::SCREEN_WIDTH, windows_rect::SCREEN_HEIGHT, D3DCOLOR_RGBA(255, 255, 255, 0), true, 0.0f, 0, 0, TextureLoder::GetTextureData(DAMEGEEFFECT01), true);
	PauseScreen_ = Polygon2D::Create(1, 450.0f, windows_rect::SCREEN_HEIGHT / 2, 700.0f, 500.0f, 0, 0, 100, 100, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(PAUSE),false);
	PauseButtonOff01_ = Polygon2D::Create(1, 490.0f, 360.0f, 550.0f, 70.0f, 0, 0, 100, 100, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(PAUSEBUTTON01_ON),false);
	PauseButtonOff02_ = Polygon2D::Create(1, 490.0f, 460.0f, 550.0f, 70.0f, 0, 0, 100, 100, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(PAUSEBUTTON02_ON),false);
	PauseButtonOn01_ = Polygon2D::Create(1, 490.0f, 360.0f, 550.0f, 70.0f, 0, 0, 100, 100, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(PAUSEBUTTON01_OFF),false);
	PauseButtonOn02_ = Polygon2D::Create(1, 490.0f, 460.0f, 550.0f, 70.0f, 0, 0, 100, 100, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(PAUSEBUTTON02_OFF),false);
	
	Polygon2D::Create(1, 1100.0f, 325.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(XBUTTON), true);
	Polygon2D::Create(1, 1200.0f, 325.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(BBUTTON), true);
	Polygon2D::Create(1, 1150.0f, 250.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(YBUTTON), true);
	Polygon2D::Create(1, 1150.0f, 425.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ABUTTON), true);
	Polygon2D::Create(1, 1105.0f, 325.0f, 100.0f, 75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(MAGIC), true);
	Polygon2D::Create(1, 1205.0f, 325.0f, 100.0f, 75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ATTACK), true);
	Polygon2D::Create(1, 1152.5f, 250.0f, 100.0f, 75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(DEF), true);
	Polygon2D::Create(1, 1152.5f, 425.0f, 100.0f, 75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ROLL), true);

	//Polygon2D::Create(1, 1100.0f, 575.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(XBUTTON), true);
	//Polygon2D::Create(1, 1200.0f, 575.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(BBUTTON), true);
	//Polygon2D::Create(1, 1150.0f, 500.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(YBUTTON), true);
	//Polygon2D::Create(1, 1150.0f, 650.0f, 100.0f, 100.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ABUTTON), true);
	//Polygon2D::Create(1, 1105.0f, 575.0f, 100.0f,  75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(MAGIC), true);
	//Polygon2D::Create(1, 1205.0f, 575.0f, 100.0f,  75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ATTACK), true);
	//Polygon2D::Create(1, 1152.5f, 500.0f, 100.0f,  75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(DEF), true);
	//Polygon2D::Create(1, 1152.5f, 650.0f, 100.0f,  75.0f, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), false, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(ROLL), true);
	player_ = Player::Create(2650,1880,2650,1880);
	boss_ = BossMonster::Create(5480, 500);
	//Instancing3D::Create();
	Sea::Create();

	sword_ = Sword::Create(0);
	shiled_ = Shiled::Create(0);

	motioneffect_ = MosionEffect::CreateMotionEffect(0);
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

Player * SceneGame::GetPlayer()
{
	return player_;
}

MyEffekseer * SceneGame::GetHitExplosion()
{
	return HitExplosion_;
}

MyEffekseer * SceneGame::GetPlayerMagicEfk()
{
	return PlayerMagicEfk_;
}

MyEffekseer * SceneGame::GetPlayerAttack01Efk()
{
	return PlayerAttack01Efk_;
}

MyEffekseer * SceneGame::GetEnemyBuf01Efk()
{
	return EnemyBuff01Efk_;
}

MyEffekseer * SceneGame::GetEnemyBuf02Efk()
{
	return EnemyBuff02Efk_;
}

MyEffekseer * SceneGame::GetMagicObjects(int i)
{
	return MagicObjects[i];
}

MyEffekseer * SceneGame::GetBossMagicAEfk()
{
	return BossMonsterMagicAEfk_;
}

MyEffekseer * SceneGame::GetBossMagicB_1Efk()
{
	return BossMonsterMagicB_1Efk_;
}

MyEffekseer * SceneGame::GetBossMagicCEfk()
{
	return BossMonsterMagicCEfk_;
}

MyEffekseer * SceneGame::GetBossBuffEfk()
{
	return BossMonsterBuffEfk_;
}

MyEffekseer * SceneGame::GetDamegeEffectONEfk()
{
	return GetDamegeEffectONEfk_;
}

MyEffekseer * SceneGame::GetBossBuff2Efk()
{
	return BossMonsterBuff2Efk_;
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

MosionEffect * SceneGame::GetMotionEffect()
{
	return motioneffect_;
}

BossMonster * SceneGame::GetBossMonster()
{
	return boss_;
}

Shiled * SceneGame::GetPlayerShiled()
{
	return shiled_;
}

Sword * SceneGame::GetPlayerSword()
{
	return sword_;
}

Polygon2D * SceneGame::GetPauseScreen()
{
	return PauseScreen_;
}

Polygon2D * SceneGame::GetPauseButton01ON()
{
	return PauseButtonOn01_;
}

Polygon2D * SceneGame::GetPauseButton02ON()
{
	return PauseButtonOn02_;
}

Polygon2D * SceneGame::GetPauseButton01OFF()
{
	return PauseButtonOff01_;
}

Polygon2D * SceneGame::GetPauseButton02OFF()
{
	return PauseButtonOff02_;
}

Polygon2D * SceneGame::GetDamegeEffect()
{
	return DamegeEffect_;
}
