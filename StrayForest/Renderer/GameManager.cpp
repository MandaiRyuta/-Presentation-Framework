#include "GameManager.h"
#include "../System/InheritanceNode/Model.h"
#include "../LoadManager/TextureLoder.h"

GameManager::GameManager(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight)
{
	renderer_ = CDX9Renderer::getInstance();
	//DirectX9�̕`��֘A�̏�����
	if (FAILED(renderer_->Init(_hWnd, _bWindow, _nWindowWidth, _nWindowHeight)))
	{
		MessageBox(NULL, "CRenderer�̏������Ɏ��s���܂����B", "�������G���[", MB_OK);
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
	device_->Clear(0,										// RECT�\���̔z��̋�`�̐�
		NULL,									// RECT�\���̂̐擪�A�h���X(��ʑS�̂�NULL)
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	// TARGET�͐F�̃N���A�AZBUFFER��Z�o�b�t�@�̃N���A
		D3DCOLOR_RGBA(30, 64, 192, 255),		// �N���A�J���\(TARGET������Ƃ�)
		1.0f,									// Z�o�b�t�@�̃N���A�l
		0);									// �X�e���V���l�̃N���A�l
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
