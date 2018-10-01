#pragma once

constexpr int OBJ_MAX = 200;
constexpr int SORT_MAX = 4;

class GameObjectManager
{
public:
	enum ObjSortNumber
	{
		OBJ_3D_MODEL,
		OBJ_3D_POLYGON,
		OBJ_2D_POLYGON,
	};
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
private:
	static GameObjectManager* object_[SORT_MAX][OBJ_MAX];
	static int PauseState_;
};