#include "../Renderer/GameManager.h"
#include "GameObjectManager.h"
#include "../InputManager/input.h"
#include "../Renderer/GameManager.h"
#include "../SceneManager/InheritanceNode/SceneGame.h"
#include "../System/Polygon2D.h"

GameObjectManager* GameObjectManager::object_[SORT_MAX][OBJ_MAX];
bool GameObjectManager::pause_;

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
	pause_ = false;
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
		if (GameManager::GetKeyboard()->GetKeyTrigger(DIK_P))
		{
			SceneGame::GetPauseScreen()->SetDraw(true);
			SceneGame::GetPauseButton01ON()->SetDraw(true);
			SceneGame::GetPauseButton01OFF()->SetDraw(false);
			SceneGame::GetPauseButton02ON()->SetDraw(false);
			SceneGame::GetPauseButton02OFF()->SetDraw(true);
			SetPause(true);
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
		if (SceneGame::GetPauseScreen()->GetDraw())
		{
			if (GameManager::GetKeyboard()->GetKeyTrigger(DIK_UP))
			{
				SceneGame::GetPauseButton01ON()->SetDraw(true);
				SceneGame::GetPauseButton01OFF()->SetDraw(false);
				SceneGame::GetPauseButton02ON()->SetDraw(false);
				SceneGame::GetPauseButton02OFF()->SetDraw(true);
			}
			else if (GameManager::GetKeyboard()->GetKeyTrigger(DIK_DOWN))
			{
				SceneGame::GetPauseButton01ON()->SetDraw(false);
				SceneGame::GetPauseButton01OFF()->SetDraw(true);
				SceneGame::GetPauseButton02ON()->SetDraw(true);
				SceneGame::GetPauseButton02OFF()->SetDraw(false);
			}
		}

		if (GameManager::GetKeyboard()->GetKeyTrigger(DIK_P))
		{
			SceneGame::GetPauseScreen()->SetDraw(false);
			SceneGame::GetPauseButton01ON()->SetDraw(false);
			SceneGame::GetPauseButton01OFF()->SetDraw(false);
			SceneGame::GetPauseButton02ON()->SetDraw(false);
			SceneGame::GetPauseButton02OFF()->SetDraw(false);
			SetPause(false);
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
