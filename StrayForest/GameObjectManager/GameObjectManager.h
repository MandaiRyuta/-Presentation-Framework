#pragma once

constexpr int OBJ_MAX = 400;
constexpr int SORT_MAX = 3;

class GameObjectManager
{
public:
	GameObjectManager(int _Priority);
	virtual ~GameObjectManager() {}
public:
	virtual void Init(){}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	void Release();
	static void UpdateAll();
	static void DrawAll();
	static void ReleaseAll();
	static void SetPause(bool _pause);
	static bool GetPause();
private:
	static bool RestartFlag_;
	static bool NonRestartFlag_;
	static bool pause_;
	static GameObjectManager* object_[SORT_MAX][OBJ_MAX];
	static int PauseState_;
};