#include "SceneTitle.h"
#include "../../../LoadManager/TextureLoder.h"
#include "../../../System/InheritanceNode/PolygonColorChanger/PolygonColorChanger.h"
#include "../../System/Sound.h"
#include "../../Renderer/GameManager.h"
Polygon2D* SceneTitle::TitleStartBar_ = nullptr;
Fade* SceneTitle::fade_;

void SceneTitle::Initialize()
{
	fade_ = Fade::Create();
	Polygon2D::Create(1, 0.f, 0.f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, 1280, 1024, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(TITLE_BACKGROUND), true);
	Polygon2D::Create(1, 80.f, -30.0f, 1000.f, 800.f, 0, 0, 1000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(TITLE_LOGO), true);
	Polygon2D::Create(1, 300.f, 180.f, 450.0f, 240.0f, 0, 0, 800, 400, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(TITLE_BATTLEEDITION), true);
	TitleStartBar_ = Polygon2D::Create(1, 150.f, 240.0f, 680.0f, 340.0f, 0, 0, 800, 400, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(TITLE_STARTBUTTON), true);
	PolygonColorChanger::Create(1);
	//GameManager::GetEffectSound()->PlaySoundA(EffectSound::SOUND_TITLE);
}

void SceneTitle::Update()
{

}

void SceneTitle::Draw()
{
}

void SceneTitle::Release()
{
	GameObjectManager::ReleaseAll();
}

Polygon2D * SceneTitle::GetTitleStartBar()
{
	return TitleStartBar_;
}

Fade * SceneTitle::GetFade()
{
	return fade_;
}
