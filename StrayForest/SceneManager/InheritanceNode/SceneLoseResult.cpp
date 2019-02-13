#include "SceneLoseResult.h"
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../../Renderer/GameManager.h"
#include "../../../System/InheritanceNode/MeshFiled.h"
#include "../../../System/InheritanceNode/Skydome.h"
#include "../../SkinMeshAnimation/ModelAnim.h"
#include "../../../System/InheritanceNode/Player/LostPlayer.h"
#include "../../System/InheritanceNode/Fade/Fade.h"
#include "../../System/Polygon2D.h"
#include "../../System/InheritanceNode/PolygonColorChanger/PolygonColorChanger.h"
#include "../../LoadManager/TextureLoder.h"

MeshFiled* SceneLoseResult::LostResultMeshFiled_ = nullptr;
LosePlayer* SceneLoseResult::LostResultPlayer_ = nullptr;
Fade* SceneLoseResult::fade_ =  nullptr;
Polygon2D* SceneLoseResult::SepiaPolygon_ = nullptr;
Polygon2D* SceneLoseResult::GameOverPolygon_ = nullptr;
bool SceneLoseResult::SepiaColorFlag_;
bool SceneLoseResult::GameOverDrawFlag_;
Polygon2D* SceneLoseResult::PressButtonWord_ = nullptr;

void SceneLoseResult::Initialize()
{
	fade_ = Fade::Create();
	Skydome::Create();
	Entity::MeshFiledSize filedsize;

	filedsize.filed_x = MeshFiledX;
	filedsize.filed_z = MeshFiledZ;
	filedsize.size_x = MeshFiledXSize;
	filedsize.size_z = MeshFiledZSize;
	
	LostResultMeshFiled_ = MeshFiled::Create(filedsize);
	LostResultPlayer_ = LosePlayer::Create(0);
	SepiaColorFlag_ = false;
	GameOverDrawFlag_ = false;
	SepiaPolygon_ = Polygon2D::Create(1, 0.0f, 0.0f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, 100, 100, D3DCOLOR_RGBA(117,83,37,0),true,0.0f,0.0f,0.0f,NULL,true);
	GameOverPolygon_ = Polygon2D::Create(1, 0.0f, 0.0f, (float)windows_rect::SCREEN_WIDTH, (float)windows_rect::SCREEN_HEIGHT, 0, 0, 100, 100, D3DCOLOR_RGBA(255, 255, 255, 0), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(RESULTLOSEWORD), true);
	PressButtonWord_ = Polygon2D::Create(1, 120.0f, 240.0f, 800.0f, 350.0f, 0, 0, 2126, 1417, D3DCOLOR_RGBA(255, 255, 255, 0), true, 0.0f, 0.0f, 0.0f, TextureLoder::GetTextureData(LOSEPOLYGONWORD), true);
	PolygonColorChanger::Create(1);
}

void SceneLoseResult::Update()
{
}

void SceneLoseResult::Draw()
{
}

void SceneLoseResult::Release()
{
	GameObjectManager::ReleaseAll();
}

MeshFiled* SceneLoseResult::GetMeshFiled()
{
	return LostResultMeshFiled_;
}

LosePlayer* SceneLoseResult::GetLostPlayer()
{
	return LostResultPlayer_;
}

Fade * SceneLoseResult::GetFade()
{
	return fade_;
}

Polygon2D * SceneLoseResult::GetSepiaPolygon()
{
	return SepiaPolygon_;
}

Polygon2D * SceneLoseResult::GetGameOverPolygon()
{
	return GameOverPolygon_;
}

Polygon2D * SceneLoseResult::GetPressButtonPolygon()
{
	return PressButtonWord_;
}

bool SceneLoseResult::GetSepiaFlag()
{
	return SepiaColorFlag_;
}

void SceneLoseResult::SetSepiaFlag(bool _flag)
{
	SepiaColorFlag_ = _flag;
}

bool SceneLoseResult::GetGameOverFlag()
{
	return GameOverDrawFlag_;
}

void SceneLoseResult::SetGameOverFlag(bool _flag)
{
	GameOverDrawFlag_ = _flag;
}
