#pragma once
#include "../main.h"
#include "../Renderer/Renderer.h"
#include "../GameObjectManager/GameObjectManager.h"

class SceneManager;
class CCamera;
class Light;
class CInputKeyboard;
class CInputMouse;

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
private:
	//ÉuÉâÅ[óp
	LPDIRECT3DTEXTURE9 m_BlurTexture1;
	LPDIRECT3DSURFACE9 m_BlurSurface1;
	LPDIRECT3DTEXTURE9 m_BlurTexture2;
	LPDIRECT3DSURFACE9 m_BlurSurface2;

	LPDIRECT3DSURFACE9 m_BackBufferSurface;
	static CInputMouse* mouse_;
	static CInputKeyboard* keyboard_;
	CDX9Renderer* renderer_;
	CCamera* camera_;
	Light* light_;
	static SceneManager* mode_;
};