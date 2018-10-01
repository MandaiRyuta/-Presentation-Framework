#include "../Renderer/GameManager.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::object_[SORT_MAX][OBJ_MAX];

GameObjectManager::GameObjectManager(int _Priority)
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
