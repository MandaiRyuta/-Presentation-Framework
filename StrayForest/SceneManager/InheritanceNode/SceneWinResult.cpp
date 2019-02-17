#include "SceneWinResult.h"
#include "../../../System/InheritanceNode/Player/WinPlayer.h"
#include "../../../System/InheritanceNode/Skydome.h"
#include "../../../System/InheritanceNode/MeshFiled.h"
#include "../..//../System/InheritanceNode/Fade/Fade.h"
#include "../../System/Polygon2D.h"
#include "../../LoadManager/TextureLoder.h"
#include "../../System/InheritanceNode/PolygonColorChanger/PolygonColorChanger.h"
#include "../../System/Sound.h"
MeshFiled* SceneWinResult::WinResultMeshFiled_ = nullptr;
WinPlayer* SceneWinResult::WinResultPlayer_ = nullptr;
Fade* SceneWinResult::fade_ = nullptr;
Polygon2D* SceneWinResult::WinWord_ = nullptr;
void SceneWinResult::Initialize()
{
	fade_ = Fade::Create();

	Skydome::Create();
	Entity::MeshFiledSize filedsize;

	filedsize.filed_x = MeshFiledX;
	filedsize.filed_z = MeshFiledZ;
	filedsize.size_x = MeshFiledXSize;
	filedsize.size_z = MeshFiledZSize;
	WinResultMeshFiled_ = MeshFiled::Create(filedsize);
	WinResultPlayer_ = WinPlayer::Create(0);
	Polygon2D::Create(1, 0.0f, -100.0f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, 2126, 1477, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(RESULTWINWORD), true);
	WinWord_ = Polygon2D::Create(1, 0.0f, 150.0f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, 2126, 1477, D3DCOLOR_RGBA(255, 255, 255, 255), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(WINPOLYGONWORD), true);
	PolygonColorChanger::Create(1);
	GameManager::GetEffectSound()->PlaySoundA(EffectSound::SOUND_LABEL::SOUND_WIN);
}

void SceneWinResult::Update()
{
}

void SceneWinResult::Draw()
{
}

void SceneWinResult::Release()
{
	GameManager::GetEffectSound()->StopSound(EffectSound::SOUND_LABEL::SOUND_WIN);
	GameObjectManager::ReleaseAll();
}

Fade * SceneWinResult::GetFade()
{
	return fade_;
}

MeshFiled * SceneWinResult::GetMeshFiled()
{
	return WinResultMeshFiled_;
}

WinPlayer * SceneWinResult::GetWinPlayer()
{
	return WinResultPlayer_;
}

Polygon2D * SceneWinResult::GetWinWord()
{
	return WinWord_;
}
