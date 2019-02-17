#pragma once
#include "../main.h"
#include "../Renderer/Renderer.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <vector>

class SceneManager;
class CCamera;
class Light;
class CInputKeyboard;
class CInputMouse;
class Models;
class GamePadXbox;
class EffectSound;
//プレイヤーの歩くスピード
constexpr float WALKSPEED = 1.0f;
//プレイヤーの走るスピード
constexpr float RUNSPEED = 3.0f;
//プレイヤーのローリングスピード
constexpr float ROLLSPEED = 4.0f;

//****************************************************
// 列挙型
//****************************************************
enum LOADMODEL
{
	MODEL_SKYDOME,
	//MODEL_TREE,
	MODEL_SHADOW,
	MODEL_SHILED,
	MODEL_SWORD,
	MODEL_MAX,	//モデルの最大個数
};

enum SCENE_NUM
{
	SCENE_TITLE,
	SCENE_CHUTORIAL,
	SCENE_GAME,
	SCENE_WINRESULT,
	SCENE_LOSERESULT,
	SCENE_MAX
};

class GameManager
{
public:
	//@Summary	GameManager	:　DirectX9の初期化
	GameManager(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight);
	~GameManager() {}
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
public:
	//@Summary	SetSceneMode	:	シーンの切り替え＆シーン番号振り
	//@Param Name	=	"_Mode"	:	シーン情報
	//@Param Name	=	"_scene_num"	:	シーン番号
	static void SetSceneMode(SceneManager* _Mode, SCENE_NUM _scene_num);
public:
	//@Summary	GetSceneNumber	:	現在のシーン番号
	static SCENE_NUM GetSceneNumber();
	//@Summary	GetKeyboard	:	キーボード情報取得関数
	static CInputKeyboard* GetKeyboard();
	//@Summary	GetMouse	:	マウス情報取得関数
	static CInputMouse* GetMouse();
	//@Summary	GetModel	:	モデル情報取得関数
	//@Param Name	=	"_modelnum"	:	モデル番号
	static Models* GetModel(LOADMODEL _modelnum);
	//@Summary	GetCamera	:	カメラ情報取得関数
	static CCamera* GetCamera();
	//@Summary	GetGamePad	:	ゲームパット情報取得関数
	static GamePadXbox* GetGamePad();
	//@Summary	GetEffectSound	:	エフェクトサウンド情報取得関数
	static EffectSound* GetEffectSound();
private:
	static GamePadXbox* GamePad_;	//ゲームパット
	static SCENE_NUM SceneNum_;	//シーン番号
	static CInputMouse* mouse_;	//マウス情報
	static CInputKeyboard* keyboard_;	//キーボード情報
	CDX9Renderer* renderer_;	//描画クラス
	static CCamera* camera_;	//カメラ情報
	Light* light_;	//ライト情報
	static SceneManager* mode_;	//シーン情報
	static std::vector<Models*> modelinfo_;	//モデル情報
	static EffectSound* sound_;	//エフェクトサウンド情報
};