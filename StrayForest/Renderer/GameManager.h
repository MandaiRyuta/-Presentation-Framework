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
	void SetSceneMode(SceneManager* _Mode);
public:
	static CInputKeyboard* GetKeyboard();
	static CInputMouse* GetMouse();
	static Models* GetModel(LOADMODEL _modelnum);
	static CCamera* GetCamera();
private:
	//static Models* modelinfo_[MODEL_MAX];
	static CInputMouse* mouse_;
	static CInputKeyboard* keyboard_;
	CDX9Renderer* renderer_;
	static CCamera* camera_;
	Light* light_;
	static SceneManager* mode_;
	static std::vector<Models*> modelinfo_;
};