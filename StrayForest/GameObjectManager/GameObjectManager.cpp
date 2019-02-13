#include "../Renderer/GameManager.h"
#include "GameObjectManager.h"
#include "../InputManager/input.h"
#include "../Renderer/GameManager.h"
#include "../SceneManager/InheritanceNode/SceneChutorial.h"
#include "../SceneManager/InheritanceNode/SceneGame.h"
#include "../SceneManager/InheritanceNode/SceneTitle.h"
#include "../SceneManager/InheritanceNode/SceneWinResult.h"
#include "../SceneManager/InheritanceNode/SceneLoseResult.h"
#include "../System/Polygon2D.h"
#include "../System/Sound.h"
GameObjectManager* GameObjectManager::object_[SORT_MAX][OBJ_MAX];
bool GameObjectManager::pause_;
bool GameObjectManager::RestartFlag_;
bool GameObjectManager::NonRestartFlag_;

GameObjectManager::GameObjectManager(int _Priority)
{
	if (_Priority < SORT_MAX)
	{
		for (int i = 0; i < OBJ_MAX; i++)
		{
			if (object_[_Priority][i] == NULL)
			{
				object_[_Priority][i] = this;
				break;
			}
		}
	}
	else
	{
		pause_ = false;
		RestartFlag_ = false;
		NonRestartFlag_ = false;
	}
}

void GameObjectManager::Release()
{
	for (int i = 0; i < SORT_MAX; i++)
	{
		for (int t = 0; t < OBJ_MAX; t++)
		{
			if (object_[i][t] == this)
			{
				object_[i][t]->Uninit();
				delete this;
				break;
			}
		}
	}
}

void GameObjectManager::UpdateAll()
{
	//ここでポーズ用のフラグを設定する
	if (!pause_)
	{
		if (GameManager::GetSceneNumber() == SCENE_TITLE)
		{
			if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_START))
			{
				//GameManager::GetEffectSound()->PlaySoundA(EffectSound::SOUND_SELECT01);
				SceneTitle::GetFade()->FadeSetNumber(1);
			}
			if (SceneTitle::GetFade()->GetFadeFlag())
			{
				GameManager::SetSceneMode(new SceneChutorial, SCENE_CHUTORIAL);
				//SetPause(false);
			}
		}
		else if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
		{
			if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_START))
			{
				SceneChutorial::GetFade()->FadeSetNumber(1);
			}
			if (SceneChutorial::GetFade()->GetFadeFlag())
			{
				GameManager::SetSceneMode(new SceneGame, SCENE_GAME);
				//SetPause(false);
			}
		}
		else if (GameManager::GetSceneNumber() == SCENE_GAME)
		{
			if (SceneGame::GetPlayer()->GetCameraMove())
			{
				if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_START))
				{
					SetPause(true);
					SceneGame::GetPauseScreen()->SetDraw(true);
					SceneGame::GetPauseButton01ON()->SetDraw(true);
					SceneGame::GetPauseButton01OFF()->SetDraw(false);
					SceneGame::GetPauseButton02ON()->SetDraw(false);
					SceneGame::GetPauseButton02OFF()->SetDraw(true);
				}
				//if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_A))
				//{
				//	GameManager::SetSceneMode(new SceneLoseResult, SCENE_LOSERESULT);
				//}
				if (SceneGame::GetPlayer()->GetLife() < 0.0f)
				{
					SceneGame::GetFade()->FadeSetNumber(1);

					if (SceneGame::GetFade()->GetFadeFlag())
					{
						GameManager::SetSceneMode(new SceneLoseResult, SCENE_LOSERESULT);
					}
				}
				else if (SceneGame::GetBossMonster()->GetLife() < 0.0f)
				{
					SceneGame::GetFade()->FadeSetNumber(1);
					if (SceneGame::GetFade()->GetFadeFlag())
					{
						GameManager::SetSceneMode(new SceneWinResult, SCENE_WINRESULT);
					}
				}
			}
		}
		else if (GameManager::GetSceneNumber() == SCENE_LOSERESULT)
		{
			if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_START))
			{
				SceneLoseResult::GetFade()->FadeSetNumber(1);
			}
			if (SceneLoseResult::GetFade()->GetFadeFlag())
			{
				GameManager::SetSceneMode(new SceneTitle, SCENE_TITLE);
				//SetPause(false);
			}
		}
		else if (GameManager::GetSceneNumber() == SCENE_WINRESULT)
		{
			if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_START))
			{
				SceneWinResult::GetFade()->FadeSetNumber(1);
			}
			if (SceneWinResult::GetFade()->GetFadeFlag())
			{
				GameManager::SetSceneMode(new SceneTitle, SCENE_TITLE);
				//SetPause(false);
			}
		}

		for (int i = 0; i < SORT_MAX; i++)
		{
			for (int t = 0; t < OBJ_MAX; t++)
			{
				if (object_[i][t] != NULL)
				{
					object_[i][t]->Update();
				}
			}
		}
	}
	else
	{
		if (GameManager::GetSceneNumber() == SCENE_GAME)
		{
			if (SceneGame::GetPauseScreen()->GetDraw())
			{
				if (GameManager::GetGamePad()->GetLeftControllerTrigger(UP))
				{
					RestartFlag_ = true;
					NonRestartFlag_ = false;
					SceneGame::GetPauseButton01ON()->SetDraw(true);
					SceneGame::GetPauseButton01OFF()->SetDraw(false);
					SceneGame::GetPauseButton02ON()->SetDraw(false);
					SceneGame::GetPauseButton02OFF()->SetDraw(true);
				}
				else if (GameManager::GetGamePad()->GetLeftControllerTrigger(DOWN))
				{
					RestartFlag_ = false;
					NonRestartFlag_ = true;
					SceneGame::GetPauseButton01ON()->SetDraw(false);
					SceneGame::GetPauseButton01OFF()->SetDraw(true);
					SceneGame::GetPauseButton02ON()->SetDraw(true);
					SceneGame::GetPauseButton02OFF()->SetDraw(false);
				}
			}

			if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_START))
			{
				SetPause(false);
				SceneGame::GetPauseScreen()->SetDraw(false);
				SceneGame::GetPauseButton01ON()->SetDraw(false);
				SceneGame::GetPauseButton01OFF()->SetDraw(false);
				SceneGame::GetPauseButton02ON()->SetDraw(false);
				SceneGame::GetPauseButton02OFF()->SetDraw(false);
			}

			if (RestartFlag_)
			{
				if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_A))
				{
					SetPause(false);
					SceneGame::GetPauseScreen()->SetDraw(false);
					SceneGame::GetPauseButton01ON()->SetDraw(false);
					SceneGame::GetPauseButton01OFF()->SetDraw(false);
					SceneGame::GetPauseButton02ON()->SetDraw(false);
					SceneGame::GetPauseButton02OFF()->SetDraw(false);
				}
			}
			if (NonRestartFlag_)
			{
				if (GameManager::GetGamePad()->GetButtonTrigger(GamePad_Button_A))
				{
					SetPause(false);
					SceneGame::GetPauseScreen()->SetDraw(false);
					SceneGame::GetPauseButton01ON()->SetDraw(false);
					SceneGame::GetPauseButton01OFF()->SetDraw(false);
					SceneGame::GetPauseButton02ON()->SetDraw(false);
					SceneGame::GetPauseButton02OFF()->SetDraw(false);
					GameManager::SetSceneMode(new SceneTitle, SCENE_TITLE);
				}
			}
		}
	}
}

void GameObjectManager::DrawAll()
{
	for (int i = 0; i < SORT_MAX; i++)
	{
		for (int t = 0; t < OBJ_MAX; t++)
		{
			if (object_[i][t] != NULL)
			{
				object_[i][t]->Draw();
			}
		}
	}
}

void GameObjectManager::ReleaseAll()
{
	for (int i = 0; i < SORT_MAX; i++)
	{
		for (int t = 0; t < OBJ_MAX; t++)
		{
			if (object_[i][t] != NULL)
			{
				object_[i][t]->Release();
				object_[i][t] = NULL;
			}
		}
	}
}

void GameObjectManager::SetPause(bool _pause)
{
	pause_ = _pause;
}

bool GameObjectManager::GetPause()
{
	return pause_;
}
