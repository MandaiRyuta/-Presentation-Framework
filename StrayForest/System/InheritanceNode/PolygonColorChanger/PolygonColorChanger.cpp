#include "PolygonColorChanger.h"
#include "../../Polygon2D.h"
#include "../../../SceneManager/InheritanceNode/SceneTitle.h"
#include "../../../SceneManager/InheritanceNode/SceneLoseResult.h"
#include "../../../SceneManager/InheritanceNode/SceneChutorial.h"
#include "../../../SceneManager/InheritanceNode/SceneWinResult.h"
PolygonColorChanger::PolygonColorChanger(int _Priority)
	: GameObjectManager(_Priority)
	, alpha_(0)
	, sepiaalpha_(0)
	, changeflag_(false)
{
}

PolygonColorChanger::~PolygonColorChanger()
{
}

void PolygonColorChanger::Init()
{
	if (GameManager::GetSceneNumber() == SCENE_TITLE)
	{
		LoadPolygon(SceneTitle::GetTitleStartBar());
	}
	if (GameManager::GetSceneNumber() == SCENE_WINRESULT)
	{
		LoadPolygon(SceneWinResult::GetWinWord());
	}
	if (GameManager::GetSceneNumber() == SCENE_LOSERESULT)
	{
		LoadPolygon(SceneLoseResult::GetGameOverPolygon());
		LoadPolygon2(SceneLoseResult::GetPressButtonPolygon());
		LoadSepiaPolygon(SceneLoseResult::GetSepiaPolygon());
	}
}

void PolygonColorChanger::Update()
{
	if (GameManager::GetSceneNumber() == SCENE_TITLE)
	{
		if (alpha_ <= 0)
		{
			changeflag_ = false;
		}
		else if (alpha_ >= 255)
		{
			changeflag_ = true;
		}

		polygon_->SetColor(D3DCOLOR_RGBA(255, 255, 255, alpha_));

		if (!changeflag_)
		{
			alpha_+= 3;
		}
		else if (changeflag_)
		{
			alpha_-= 3;
		}
	}
	if (GameManager::GetSceneNumber() == SCENE_WINRESULT)
	{
		if (alpha_ <= 0)
		{
			changeflag_ = false;
		}
		else if (alpha_ >= 255)
		{
			changeflag_ = true;
		}

		polygon_->SetColor(D3DCOLOR_RGBA(255, 255, 255, alpha_));
		
		if (!changeflag_)
		{
			alpha_ += 3;
		}
		else if (changeflag_)
		{
			alpha_ -= 3;
		}
	}
	if (GameManager::GetSceneNumber() == SCENE_LOSERESULT)
	{

		if (SceneLoseResult::GetSepiaFlag() == true)
		{
			polygon2_->SetColor(D3DCOLOR_RGBA(117, 83, 37, sepiaalpha_));

			if (sepiaalpha_ <= 128)
			{
				sepiaalpha_++;
			}
			else if (sepiaalpha_ > 128)
			{
				SceneLoseResult::SetGameOverFlag(true);
			}
		}
		if (SceneLoseResult::GetGameOverFlag() == true)
		{
			if (alpha2_ <= 0)
			{
				changeflag_ = false;
			}
			else if (alpha2_ >= 255)
			{
				changeflag_ = true;
			}

			polygon_->SetColor(D3DCOLOR_RGBA(255, 255, 255, alpha_));
			polygon3_->SetColor(D3DCOLOR_RGBA(255, 255, 255, alpha2_));
			if (alpha_ < 255)
			{
				alpha_+= 3;
			}

			if (!changeflag_)
			{
				alpha2_ += 3;
			}
			else if (changeflag_)
			{
				alpha2_ -= 3;
			}
		}
	}
}

void PolygonColorChanger::Draw()
{
}

void PolygonColorChanger::Uninit()
{
}

PolygonColorChanger * PolygonColorChanger::Create(int _Priority)
{
	PolygonColorChanger* ColorChanger = new PolygonColorChanger(_Priority);
	ColorChanger->Init();
	return ColorChanger;
}

void PolygonColorChanger::LoadPolygon(Polygon2D * target)
{
	polygon_ = target;
}

void PolygonColorChanger::LoadPolygon2(Polygon2D * target)
{
	polygon3_ = target;
}

void PolygonColorChanger::LoadSepiaPolygon(Polygon2D* target)
{
	polygon2_ = target;
}