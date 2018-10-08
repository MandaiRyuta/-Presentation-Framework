#include "GameManager.h"
#include "../SceneManager/SceneManager.h"
#include "../SceneManager/InheritanceNode/SceneTitle.h"
#include "../SceneManager/InheritanceNode/SceneGame.h"
#include "../SceneManager/InheritanceNode/SceneResult.h"
#include "../LoadManager/ModelLoder.h"
#include "../LoadManager/TextureLoder.h"
#include "../ShaderManager/EffectShaderManager.h"
#include "../System/InheritanceNode/Camera.h"
#include "../System/InheritanceNode/Light.h"
#include "../InputManager/input.h"

SceneManager* GameManager::mode_;
CInputKeyboard* GameManager::keyboard_;

GameManager::GameManager(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight)
{
	_hInstance = _hInstance;

	renderer_ = CDX9Renderer::getInstance();
	//DirectX9の描画関連の初期化
	if (FAILED(renderer_->Init(_hWnd, _bWindow, _nWindowWidth, _nWindowHeight)))
	{
		MessageBox(NULL, "CRendererの初期化に失敗しました。", "初期化エラー", MB_OK);
		PostQuitMessage(0);
	}
	keyboard_ = new CInputKeyboard();
	keyboard_->Init(_hInstance, _hWnd);

	camera_ = new CCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 200.0f, -100.0f));
	light_ = new Light();
	light_->Init();
}

void GameManager::Init()
{
	/*読み込むテクスチャは先に読み込ませておく*/
	TextureLoder::LoadData("Resource/Texture/floor01.png");
	TextureLoder::LoadData("Resource/Texture/floor02.png");
	//TextureLoder::LoadData("Resource/Texture/floor01normal.png");
	//TextureLoder::LoadData("Resource/Texture/floor02normal.png");
	ModelLoder::LoadData("Resource/Model/skydomemodel.x");
	ModelLoder::LoadData("Resource/Model/treemodel.x");
	EffectShaderManager::EffectLoad("Resource/Shader/ModelShader.fx");
	EffectShaderManager::EffectLoad("Resource/Shader/Instance3D.fx");
	//EffectShaderManager::EffectLoad("Resource/Shader/BumpMap.fx");
	SetSceneMode(new SceneGame);
}

void GameManager::Update()
{
	camera_->CameraUpdate();
	keyboard_->Update();
	GameObjectManager::UpdateAll();
}

void GameManager::Draw()
{
	LPDIRECT3DDEVICE9 device_ = GetDevice();
	device_->Clear(0,										// RECT構造体配列の矩形の数
		NULL,									// RECT構造体の先頭アドレス(画面全体はNULL)
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	// TARGETは色のクリア、ZBUFFERはZバッファのクリア
		D3DCOLOR_RGBA(30, 64, 192, 255),		// クリアカラ―(TARGETがあるとき)
		1.0f,									// Zバッファのクリア値
		0);									// ステンシル値のクリア値
	SUCCEEDED(device_->BeginScene());
	
	ImGui::GetFPS();

	GameObjectManager::DrawAll();

	ImGui::Render();

	device_->EndScene();
	device_->Present(NULL, NULL, NULL, NULL);
}

void GameManager::Uninit()
{
	if (renderer_ != nullptr)
	{
		renderer_->Uninit();
	}

	if (mode_ != nullptr)
	{
		mode_->Release();
		delete mode_;
		mode_ = nullptr;
	}

	if (camera_ != nullptr)
	{
		camera_->CameraUninit();
		delete camera_;
		camera_ = nullptr;
	}

	if (light_ != nullptr)
	{
		light_->Uninit();
		delete light_;
		light_ = nullptr;
	}
	
	if (keyboard_ != nullptr)
	{
		keyboard_->Uninit();
		delete keyboard_;
		keyboard_ = nullptr;
	}
	TextureLoder::RelaseAll();
	ModelLoder::ReleseAll();
	EffectShaderManager::ReleaseAll();
}

void GameManager::SetSceneMode(SceneManager * _Mode)
{
	if (mode_ != nullptr) {
		mode_->Release();
		delete mode_;
		mode_ = nullptr;
	}

	mode_ = _Mode;

	if (mode_ != nullptr)
	{
		mode_->Initialize();
	}
}

CInputKeyboard * GameManager::GetKeyboard()
{
	return keyboard_;
}
