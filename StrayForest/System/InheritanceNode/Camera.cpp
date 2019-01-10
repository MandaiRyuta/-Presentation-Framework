#include "camera.h"

#include "../../InputManager/input.h"
#include "../../Renderer/GameManager.h"
#include "Player\Player.h"
#include "../../SceneManager/InheritanceNode/SceneGame.h"
D3DXMATRIX CCamera::matrix_view;
D3DXMATRIX CCamera::matrix_projection;
Entity::CameraInfo CCamera::camerainfo_;
Entity::YawPitchRoll CCamera::yawpitchroll_;
CCamera::~CCamera()
{
}

void CCamera::CameraUpdate()
{
	constexpr float SPEED = 0.1f;
	LPDIRECT3DDEVICE9 device = GetDevice();
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = GameManager::GetKeyboard();
	
	D3DXMATRIX CameraRotation;
	D3DXMatrixIdentity(&CameraRotation);

	if (pInputKeyboard->GetKeyPress(DIK_UP))
	{
		yawpitchroll_.pitch += D3DXToRadian(3.0f);
	}
	if (pInputKeyboard->GetKeyPress(DIK_DOWN))
	{
		yawpitchroll_.pitch += D3DXToRadian(-3.0f);
	}
	if (pInputKeyboard->GetKeyPress(DIK_RIGHT))
	{
		yawpitchroll_.yaw += D3DXToRadian(-3.0f);
	}
	if (pInputKeyboard->GetKeyPress(DIK_LEFT))
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
		if (pInputKeyboard->GetKeyPress(DIK_DOWN))
		{
			zoom_ += -0.002f;
		}
	}
	if (!pInputKeyboard->GetKeyPress(DIK_DOWN))
	{
		if (zoom_ <= D3DX_PI / 3)
		{
			zoom_ += 0.002f;
		}
	}
	if (zoom_ <= D3DX_PI / 5)
	{
		zoom_ = D3DX_PI / 5;
	}
	//
	D3DXMatrixRotationYawPitchRoll(&CameraRotation, yawpitchroll_.yaw, yawpitchroll_.pitch, yawpitchroll_.roll);

	offset_ = D3DXVECTOR3(0.0f, 20.f, -200.0f);
	D3DXVec3TransformCoord(&offset_, &offset_, &CameraRotation);

	camerainfo_.eye = offset_ + D3DXVECTOR3(SceneGame::GetPlayer()->GetPlayerPosMatrix()._41, SceneGame::GetPlayer()->GetPlayerPosMatrix()._42, SceneGame::GetPlayer()->GetPlayerPosMatrix()._43);

	camerainfo_.at = D3DXVECTOR3(SceneGame::GetPlayer()->GetPlayerPosMatrix()._41, SceneGame::GetPlayer()->GetPlayerPosMatrix()._42, SceneGame::GetPlayer()->GetPlayerPosMatrix()._43);

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
