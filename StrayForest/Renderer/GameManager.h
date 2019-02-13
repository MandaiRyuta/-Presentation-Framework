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
constexpr float WALKSPEED = 1.0f;
constexpr float RUNSPEED = 3.0f;
constexpr float ROLLSPEED = 4.0f;

//****************************************************
// óÒãìå^
//****************************************************
enum LOADMODEL
{
	MODEL_SKYDOME,
	MODEL_TREE,
	MODEL_SHADOW,
	MODEL_SHILED,
	MODEL_SWORD,
	MODEL_MAX,	//ÉÇÉfÉãÇÃç≈ëÂå¬êî
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
	GameManager(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight);
	~GameManager() {}

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
public:
	static void SetSceneMode(SceneManager* _Mode, SCENE_NUM _scene_num);
public:
	static SCENE_NUM GetSceneNumber();
	static CInputKeyboard* GetKeyboard();
	static CInputMouse* GetMouse();
	static Models* GetModel(LOADMODEL _modelnum);
	static CCamera* GetCamera();
	static GamePadXbox* GetGamePad();
	static EffectSound* GetEffectSound();
private:
	static GamePadXbox* GamePad_;
	static SCENE_NUM SceneNum_;
	//static Models* modelinfo_[MODEL_MAX];
	static CInputMouse* mouse_;
	static CInputKeyboard* keyboard_;
	CDX9Renderer* renderer_;
	static CCamera* camera_;
	Light* light_;
	static SceneManager* mode_;
	static std::vector<Models*> modelinfo_;
	static EffectSound* sound_;
};