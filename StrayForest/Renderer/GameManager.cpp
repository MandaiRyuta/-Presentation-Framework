#include "GameManager.h"
#include "../SceneManager/SceneManager.h"
#include "../SceneManager/InheritanceNode/SceneChutorial.h"
#include "../SceneManager/InheritanceNode/SceneTitle.h"
#include "../SceneManager/InheritanceNode/SceneGame.h"
#include "../SceneManager/InheritanceNode/SceneWinResult.h"
#include "../SceneManager/InheritanceNode/SceneLoseResult.h"
#include "../LoadManager/ModelLoder.h"
#include "../LoadManager/TextureLoder.h"
#include "../ShaderManager/EffectShaderManager.h"
#include "../System/InheritanceNode/Camera.h"
#include "../System/InheritanceNode/Light.h"
#include "../InputManager/input.h"
#include <algorithm>
#include "../InputManager/XBoxController.h"
#include "../System/Sound.h"

SceneManager* GameManager::mode_;
CInputKeyboard* GameManager::keyboard_;
CInputMouse* GameManager::mouse_;
//Models* GameManager::modelinfo_[MODEL_MAX] = {};
std::vector<Models*> GameManager::modelinfo_;
CCamera* GameManager::camera_;
SCENE_NUM GameManager::SceneNum_;
GamePadXbox* GameManager::GamePad_;
EffectSound* GameManager::sound_;
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
	
	sound_ = new EffectSound();
	sound_->InitSound(_hWnd);
	sound_->InitEffectSound();

	keyboard_ = new CInputKeyboard();
	keyboard_->Init(_hInstance, _hWnd);

	mouse_ = new CInputMouse();
	mouse_->Init(_hInstance, _hWnd);

	camera_ = new CCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 200.0f, -100.0f));
	light_ = new Light();
	light_->Init();

	GamePad_ = new GamePadXbox(GamePadIndex_One, 1);


	SceneNum_ = SCENE_CHUTORIAL;
}

void GameManager::Init()
{
	/*読み込むテクスチャは先に読み込ませておく*/
	TextureLoder::LoadData("Resource/Texture/floor01.png");
	TextureLoder::LoadData("Resource/Texture/floor02.png");
	TextureLoder::LoadData("Resource/Texture/floor01normal.png");
	TextureLoder::LoadData("Resource/Texture/floor02normal.png");
	TextureLoder::LoadData("Resource/Texture/sea.png");
	TextureLoder::LoadData("Resource/Texture/Particle.png");
	TextureLoder::LoadData("Resource/Texture/motioneffect.png");
	TextureLoder::LoadData("Resource/Texture/base3.png");
	TextureLoder::LoadData("Resource/Texture/hp.png");
	TextureLoder::LoadData("Resource/Texture/mana.png");
	TextureLoder::LoadData("Resource/Texture/waku_bugs.png");
	TextureLoder::LoadData("Resource/Texture/button_bugs1.png");
	TextureLoder::LoadData("Resource/Texture/button_bugs2.png");
	TextureLoder::LoadData("Resource/Texture/empty.png");
	TextureLoder::LoadData("Resource/Texture/waku_bugs.png");
	TextureLoder::LoadData("Resource/Texture/button_bugs1.png");
	TextureLoder::LoadData("Resource/Texture/button_bugs2.png");
	TextureLoder::LoadData("Resource/Texture/button_bugs1_1.png");
	TextureLoder::LoadData("Resource/Texture/button_bugs2_1.png");
	TextureLoder::LoadData("Resource/Texture/DamegeEffect01.png");
	TextureLoder::LoadData("Resource/Texture/AButton.png");
	TextureLoder::LoadData("Resource/Texture/BButton.png");
	TextureLoder::LoadData("Resource/Texture/XButton.png");
	TextureLoder::LoadData("Resource/Texture/YButton.png");
	TextureLoder::LoadData("Resource/Texture/Roll.png");
	TextureLoder::LoadData("Resource/Texture/sword.png");
	TextureLoder::LoadData("Resource/Texture/magic.png");
	TextureLoder::LoadData("Resource/Texture/shiled.png");
	TextureLoder::LoadData("Resource/Texture/Controlbutton01.png");
	TextureLoder::LoadData("Resource/Texture/Controlbutton02.png");
	TextureLoder::LoadData("Resource/Texture/SideButton.png");
	TextureLoder::LoadData("Resource/Texture/move.png");
	TextureLoder::LoadData("Resource/Texture/hiru.png");
	TextureLoder::LoadData("Resource/Texture/BattleEdition.png");
	TextureLoder::LoadData("Resource/Texture/StartButton.png");
	TextureLoder::LoadData("Resource/Texture/logo.png");
	TextureLoder::LoadData("Resource/Texture/tutorial.png");
	TextureLoder::LoadData("Resource/Texture/tutorialset.png");
	TextureLoder::LoadData("Resource/Texture/GameClear.png");
	TextureLoder::LoadData("Resource/Texture/youdied.png");
	TextureLoder::LoadData("Resource/Texture/WinPolygon.png");
	TextureLoder::LoadData("Resource/Texture/LosePolygon.png");
	TextureLoder::LoadData("Resource/Texture/GameStartPolygon.png");
	TextureLoder::LoadData("Resource/Texture/setumei.png");
	modelinfo_.push_back(new ModelLoder("Resource/Model/skydomemodel.x"));
	modelinfo_.push_back(new ModelLoder("Resource/Model/treemodel.x"));
	modelinfo_.push_back(new ModelLoder("Resource/Model/Shadow.x"));
	modelinfo_.push_back(new ModelLoder("Resource/Model/Shiled.x"));
	modelinfo_.push_back(new ModelLoder("Resource/Model/Sword.x"));
	//modelinfo_[MODEL_SKYDOME] = new ModelLoder("Resource/Model/skydomemodel.x");
	//modelinfo_[MODEL_SHADOW] = new ModelLoder("Resource/Model/Shadow.x");
	//modelinfo_[MODEL_SHILED] = new ModelLoder("Resource/Model/Shiled.x");
	//modelinfo_[MODEL_SWORD] = new ModelLoder("Resource/Model/Sword.x");
	EffectShaderManager::EffectLoad("Resource/Shader/ModelShader.fx");
	EffectShaderManager::EffectLoad("Resource/Shader/Instance3D.fx");
	EffectShaderManager::EffectLoad("Resource/Shader/SkinMeshShader.fx");
	EffectShaderManager::EffectLoad("Resource/Shader/Guardian.fx");
	EffectShaderManager::EffectLoad("Resource/Shader/StenshillShadow.fx");
	EffectShaderManager::EffectLoad("Resource/Shader/Shiled.fx");
	EffectShaderManager::EffectLoad("Resource/Shader/Sword.fx");
	EffectShaderManager::EffectLoad("Resource/Shader/Particle.fx");
	//EffectShaderManager::EffectLoad("Resource/Shader/BumpMap.fx");
	SetSceneMode(new SceneGame, SCENE_GAME);
}

void GameManager::Update()
{
	camera_->CameraUpdate();
	keyboard_->Update();
	mouse_->Update();

	if (GamePad_->is_connected())
	{
		GamePad_->update();
	}

	GameObjectManager::UpdateAll();
}

void GameManager::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	device->Clear(0,										// RECT構造体配列の矩形の数
		NULL,									// RECT構造体の先頭アドレス(画面全体はNULL)
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),	// TARGETは色のクリア、ZBUFFERはZバッファのクリア STENCIL ステンシルシャドウの実装のために設定
		D3DCOLOR_RGBA(30, 64, 192, 255),		// クリアカラ―(TARGETがあるとき)
		1.0f,									// Zバッファのクリア値
		0);									// ステンシル値のクリア値
	SUCCEEDED(device->BeginScene());

	device->SetRenderState(D3DRS_DITHERENABLE, D3DFILL_FORCE_DWORD);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_CLIPPING, TRUE);

	GameObjectManager::DrawAll();

	//ImGui::GetFPS();

	ImGui::Render();

	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

void GameManager::Uninit()
{
	//for (int i = 0; i < MODEL_MAX; i++)
	//{
	//	modelinfo_[i]->Relese();
	//	delete modelinfo_[i];
	//}

	for (DWORD i = 0; i < modelinfo_.size(); i++)
	{
		modelinfo_[i]->Relese();
		delete modelinfo_[i];
		modelinfo_[i] = nullptr;
	}

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
	if (mouse_ != nullptr)
	{
		mouse_->Uninit();
		delete mouse_;
		mouse_ = nullptr;
	}
	if (GamePad_ != nullptr)
	{
		delete GamePad_;
		GamePad_ = nullptr;
	}

	if (sound_ != nullptr)
	{
		sound_->UninitSound();
		delete sound_;
		sound_ = nullptr;
	}

	TextureLoder::RelaseAll();
	
	EffectShaderManager::ReleaseAll();
}

void GameManager::SetSceneMode(SceneManager * _Mode, SCENE_NUM _scene_num)
{
	if (mode_ != nullptr) {
		mode_->Release();
		delete mode_;
		mode_ = nullptr;
	}

	camera_->CameraReset();
	mode_ = _Mode;
	SceneNum_ = _scene_num;

	if (mode_ != nullptr)
	{
		mode_->Initialize();
	}
}

SCENE_NUM GameManager::GetSceneNumber()
{
	return SceneNum_;
}

CInputKeyboard * GameManager::GetKeyboard()
{
	return keyboard_;
}

CInputMouse * GameManager::GetMouse()
{
	return mouse_;
}

Models* GameManager::GetModel(LOADMODEL _modelnum)
{
	return modelinfo_[_modelnum];
}

CCamera * GameManager::GetCamera()
{
	return camera_;
}

GamePadXbox * GameManager::GetGamePad()
{
	return GamePad_;
}

EffectSound * GameManager::GetEffectSound()
{
	return sound_;
}
