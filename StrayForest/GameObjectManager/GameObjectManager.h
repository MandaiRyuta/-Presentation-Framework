#pragma once
//オブジェクトの情報の最大取得数
constexpr int OBJ_MAX = 400;
//描画種類
constexpr int SORT_MAX = 3;

class GameObjectManager
{
public:
	//@Summary	GameObjectManager	:	描画種類を決めて描画情報を取り込む
	GameObjectManager(int _Priority);
	virtual ~GameObjectManager() {}
public:
	virtual void Init(){}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	void Release();
	//@Summary	UpdateAll	:	描画情報を全て更新
	static void UpdateAll();
	//@Summary	DrawAll	:	描画情報をすべて描画させる
	static void DrawAll();
	//@Summary	ReleaseAll	:	描画した情報のすべてを解放
	static void ReleaseAll();
	//@Summary SetPause	:	ポーズフラグを設定する関数
	//@ParamName	=	"_pause"	:	ポーズフラグ
	static void SetPause(bool _pause);
	//@Summary	GetPause	:	現在のポーズのフラグを取得する
	static bool GetPause();
private:
	static bool RestartFlag_;	//リスタートフラグ変数
	static bool NonRestartFlag_;	//リスタートしないフラグ変数
	static bool pause_;	//ポーズフラグ変数
	static GameObjectManager* object_[SORT_MAX][OBJ_MAX];	//オブジェクトを取り込む変数
	static int PauseState_;	//ポーズ時選択するときに使う変数
};