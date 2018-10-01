#include "GameManager.h"
#include "../System/InheritanceNode/Model.h"
#include "../LoadManager/TextureLoder.h"

GameManager::GameManager(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight)
{
	renderer_ = CDX9Renderer::getInstance();
	//DirectX9の描画関連の初期化
	if (FAILED(renderer_->Init(_hWnd, _bWindow, _nWindowWidth, _nWindowHeight)))
	{
		MessageBox(NULL, "CRendererの初期化に失敗しました。", "初期化エラー", MB_OK);
		PostQuitMessage(0);
	}


}

void GameManager::Init()
{
	TextureLoder::LoadData("images.jpg");
}

void GameManager::Update()
{
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
	TextureLoder::RelaseAll();
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
