#include "camera.h"
#include "../../InputManager/input.h"
#include "../../Renderer/GameManager.h"
#include "Player\Player.h"
#include "Player\ChutorialPlayer.h"
#include "Player\LostPlayer.h"
#include "Player\WinPlayer.h"
#include "../Polygon2D.h"
#include "../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../SceneManager/InheritanceNode/SceneChutorial.h"
#include "../../SceneManager/InheritanceNode/SceneWinResult.h"
#include "../../SceneManager/InheritanceNode/SceneLoseResult.h"

D3DXMATRIX CCamera::matrix_view;
D3DXMATRIX CCamera::matrix_projection;
Entity::CameraInfo CCamera::camerainfo_;
Entity::YawPitchRoll CCamera::yawpitchroll_;
CCamera::~CCamera()
{
}

void CCamera::CameraReset()
{
	front_ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	right_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	up_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Dot_ = 0.0f;
	camerainfo_.at = resetat_;
	camerainfo_.eye = reseteye_;
	camerainfo_.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	offset_ = D3DXVECTOR3(0.0f, 20.0f, -200.0f);
	zoom_ = D3DX_PI / 3;
	lostcamerachangetime_ = 0;
	lostzoomtime_ = 0;
	yawpitchroll_.pitch = 0.0f;
	yawpitchroll_.roll = 0.0f;
	yawpitchroll_.yaw = 0.0f;
	lostresultoffset_ = D3DXVECTOR3(offset_.x, offset_.y, offset_.z + 120.0f);
	GameStartOffset_ = offset_;
	gamestarttime_ = 0;
	gamecameraflag_ = false;
	resettime_ = 0;
	alpha01_ = 0;
	alpha01flag_ = false;
	alpha02_ = 0;
	alpha02flag_ = false;
	drawtime_ = 0;
	drawflag_ = false;
	gamestartflag_ = false;
}

void CCamera::CameraUpdate()
{
	GamePad_ = GameManager::GetGamePad();
	constexpr float SPEED = 0.1f;
	LPDIRECT3DDEVICE9 device = GetDevice();
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = GameManager::GetKeyboard();
	
	D3DXMATRIX CameraRotation;
	D3DXMatrixIdentity(&CameraRotation);
	if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
	{
		if (GamePad_->GetState()._right_thumbstick.y > 0.25f)
		{
			yawpitchroll_.pitch += D3DXToRadian(3.0f);
		}
		if (GamePad_->GetState()._right_thumbstick.y < -0.25f)
		{
			yawpitchroll_.pitch += D3DXToRadian(-3.0f);
		}
		if (GamePad_->GetState()._right_thumbstick.x > 0.25f)
		{
			yawpitchroll_.yaw += D3DXToRadian(-3.0f);
		}
		if (GamePad_->GetState()._right_thumbstick.x < -0.25f)
		{
			yawpitchroll_.yaw += D3DXToRadian(3.0f);
		}
		if (yawpitchroll_.pitch >= D3DXToRadian(75.0f))
		{
			yawpitchroll_.pitch = D3DXToRadian(75.0f);
		}
		else if (yawpitchroll_.pitch <= D3DXToRadian(0.0f))
		{
			yawpitchroll_.pitch = D3DXToRadian(0.0f);
			//if (pInputKeyboard->GetKeyPress(DIK_DOWN))
			//{
			//	zoom_ += -0.002f;
			//}
		}
	}
	if (GameManager::GetSceneNumber() == SCENE_GAME)
	{
		if (!GameObjectManager::GetPause() && SceneGame::GetPlayer()->GetCameraMove())
		{
			if (GamePad_->GetState()._right_thumbstick.y > 0.25f)
			{
				yawpitchroll_.pitch += D3DXToRadian(3.0f);
			}
			if (GamePad_->GetState()._right_thumbstick.y < -0.25f)
			{
				yawpitchroll_.pitch += D3DXToRadian(-3.0f);
			}
			if (GamePad_->GetState()._right_thumbstick.x > 0.25f)
			{
				yawpitchroll_.yaw += D3DXToRadian(-3.0f);
			}
			if (GamePad_->GetState()._right_thumbstick.x < -0.25f)
			{
				yawpitchroll_.yaw += D3DXToRadian(3.0f);
			}
			if (yawpitchroll_.pitch >= D3DXToRadian(75.0f))
			{
				yawpitchroll_.pitch = D3DXToRadian(75.0f);
			}
			else if (yawpitchroll_.pitch <= D3DXToRadian(0.0f))
			{
				yawpitchroll_.pitch = D3DXToRadian(0.0f);
				//if (pInputKeyboard->GetKeyPress(DIK_DOWN))
				//{
				//	zoom_ += -0.002f;
				//}
			}
			//if (!pInputKeyboard->GetKeyPress(DIK_DOWN))
			//{
			//	if (zoom_ <= D3DX_PI / 3)
			//	{
			//		zoom_ += 0.002f;
			//	}
			//}
			//if (zoom_ <= D3DX_PI / 5)
			//{
			//	zoom_ = D3DX_PI / 5;
			//}
		}
	}
	//
	D3DXMatrixRotationYawPitchRoll(&CameraRotation, yawpitchroll_.yaw, yawpitchroll_.pitch, yawpitchroll_.roll);
	if (GameManager::GetSceneNumber() == SCENE_GAME)
	{
		if (SceneGame::GetPlayer()->GetCameraMove())
		{
			offset_ = D3DXVECTOR3(-8.0f, 20.f, -200.0f);
		}
	}
	else if (GameManager::GetSceneNumber() != SCENE_GAME)
	{
		offset_ = D3DXVECTOR3(0.0f, 20.0f, -200.0f);
	}
	D3DXVec3TransformCoord(&offset_, &offset_, &CameraRotation);
	D3DXVec3TransformCoord(&GameStartOffset_, &GameStartOffset_, &CameraRotation);
	if (GameManager::GetSceneNumber() == SCENE_CHUTORIAL)
	{
		gamestarttime_ = 0;
		SceneChutorial::GetRightController()->SetControllPosX(GamePad_->GetState()._right_thumbstick.x);
		SceneChutorial::GetRightController()->SetControllPosY(GamePad_->GetState()._right_thumbstick.y);

		camerainfo_.eye = offset_ + SceneChutorial::GetChutorialPlayer()->GetPosition();

		camerainfo_.at = SceneChutorial::GetChutorialPlayer()->GetPosition();
	}
	if (GameManager::GetSceneNumber() == SCENE_GAME)
	{
		if (!SceneGame::GetPlayer()->GetCameraMove())
		{
			if (!gamecameraflag_)
			{
				if (gamestarttime_ < 380)
				{
					offset_.y += 0.1f;
					offset_.z += 0.02f;
					yawpitchroll_.yaw += D3DXToRadian(0.005f);
				}
				else
				{
					yawpitchroll_.yaw = 0.0f;
					gamecameraflag_ = true;
				}

				gamestarttime_++;
			}
			if (gamecameraflag_)
			{
				if (resettime_ < 380)
				{
					if (offset_.y >= 20.0f)
					{
						offset_.y -= 0.1f;
					}
					else
					{
						offset_.y = 20.0f;
					}
					if (offset_.z >= -200.0f)
					{
						offset_.z -= 0.02f;
					}
					else
					{
						offset_.z = -200.0f;
					}
				}
				else
				{
					if (!drawflag_)
					{
						if (alpha01_ < 128)
						{
							alpha01_ += 3;
						}
						else
						{
							alpha01_ = 128;
							alpha01flag_ = true;
						}

						if (alpha01flag_)
						{
							if (alpha02_ < 255)
							{
								alpha02_ += 5;
							}
							else
							{
								alpha02_ = 255;
								alpha02flag_ = true;
							}
						}

						if (alpha02flag_)
						{
							if (drawtime_ < 100)
							{
								drawtime_++;
							}
							else
							{
								drawflag_ = true;
							}
						}
					}

					if (drawflag_)
					{
						if (alpha01_ > 0)
						{
							alpha01_-= 2;
						}
						else
						{
							alpha01_ = 0;
							SceneGame::GetGameStartPolygon01()->SetDraw(false);
						}

						if (alpha02_ > 0)
						{
							alpha02_ -= 5;
							alpha01flag_ = false;
							alpha02flag_ = false;
						}
						else
						{
							alpha02_ = 0;
							SceneGame::GetGameStartpolygon02()->SetDraw(false);
							gamestartflag_ = true;
						}
					}

					SceneGame::GetGameStartPolygon01()->SetColor(D3DCOLOR_RGBA(0, 0, 0, alpha01_));
					SceneGame::GetGameStartpolygon02()->SetColor(D3DCOLOR_RGBA(255,255,255, alpha02_));

					if (gamestartflag_)
					{
						SceneGame::GetBossMonster()->SetCameraMoveFlag(true);
						SceneGame::GetPlayer()->SetCameraMove(true);
					}
				}
				resettime_++;
			}
		}
		camerainfo_.eye = offset_ + SceneGame::GetPlayer()->GetPlayerPosition();

		camerainfo_.at = SceneGame::GetPlayer()->GetPlayerPosition();
	}
	if (GameManager::GetSceneNumber() == SCENE_WINRESULT)
	{
		D3DXVECTOR3 winresultoffset;
		winresultoffset = D3DXVECTOR3(0.0f, 20.f, -80.0f);
		D3DXVECTOR3 ResultPlayerPos = SceneWinResult::GetWinPlayer()->GetPlayerPos();
	
		camerainfo_.eye = winresultoffset + ResultPlayerPos;
		camerainfo_.at = D3DXVECTOR3(ResultPlayerPos.x, ResultPlayerPos.y + 25.0f, ResultPlayerPos.z);
	}
	if (GameManager::GetSceneNumber() == SCENE_LOSERESULT)
	{
		D3DXVECTOR3 ResultPlayerPos = SceneLoseResult::GetLostPlayer()->GetPlayerPos();

		if (SceneLoseResult::GetLostPlayer()->DeadFlag())
		{
			if (lostcamerachangetime_ < 200)
			{
				lostresultoffset_.y += 1.0f;
			}
			if (lostcamerachangetime_ <= 350)
			{
				zoom_ += -0.002f;
			}
			else
			{
				SceneLoseResult::SetSepiaFlag(true);
			}
			lostcamerachangetime_++;
		}

		camerainfo_.eye = lostresultoffset_ + SceneLoseResult::GetLostPlayer()->GetPlayerPos();
		camerainfo_.at = D3DXVECTOR3(SceneLoseResult::GetLostPlayer()->GetPlayerPos().x, SceneLoseResult::GetLostPlayer()->GetPlayerPos().y + 25.0f, SceneLoseResult::GetLostPlayer()->GetPlayerPos().z);
	}

	//ビュー行列の作成
	D3DXMatrixLookAtLH(
		&this->matrix_view,
		&camerainfo_.eye,
		&camerainfo_.at,
		&camerainfo_.up
	);

	//プロジェクション行列の作成
	D3DXMatrixPerspectiveFovLH(&this->matrix_projection, zoom_ /*D3DX_PI / 3 /*D3DXToRadian(60),*/, (float)windows_rect::SCREEN_WIDTH / windows_rect::SCREEN_HEIGHT, 1.f, 10000.0f);

	//各種類行列の設定
	device->SetTransform(D3DTS_VIEW, &this->matrix_view);
	device->SetTransform(D3DTS_PROJECTION, &this->matrix_projection);
}

void CCamera::SetEye(D3DXVECTOR3 _eye)
{
	camerainfo_.eye += _eye;
}

void CCamera::SetAt(D3DXVECTOR3 _at)
{
	camerainfo_.at = _at;
}

D3DXMATRIX CCamera::GetView()
{
	return matrix_view;
}

D3DXMATRIX CCamera::GetProj()
{
	return matrix_projection;
}

D3DXVECTOR3 CCamera::GetAt()
{
	return camerainfo_.at;
}

D3DXVECTOR3 CCamera::GetEye()
{
	return camerainfo_.eye;
}

Entity::YawPitchRoll CCamera::GetYawPitchRoll()
{
	return yawpitchroll_;
}

void CCamera::SetView(D3DXMATRIX _view)
{
	matrix_view = _view;
}

void CCamera::SetProj(D3DXMATRIX _proj)
{
	matrix_projection = _proj;
}
