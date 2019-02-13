#pragma once
#include "../../Entity/Entity.h"
#include "../../InputManager/XBoxController.h"

class CCamera
{
private:
	// ビュー変換行列( 4×4のfloat行列 )
	static D3DXMATRIX matrix_view;
	// プロジェクション変換行列( 4×4のfloat行列 )
	static D3DXMATRIX matrix_projection;

	D3DXVECTOR3 offset_;
	D3DXVECTOR3 front_;
	D3DXVECTOR3 right_;
	D3DXVECTOR3 up_;
	bool gamecameraflag_;
	int resettime_;
	float zoom_;
	float m_Dot_;
	D3DXMATRIX atrotation_;
	static Entity::CameraInfo camerainfo_;
	static Entity::YawPitchRoll yawpitchroll_;
	D3DXMATRIX mtx_right_;
	D3DXMATRIX mtx_up_;
	int lostcamerachangetime_;
	int lostzoomtime_;
	int gamestarttime_;
	bool alpha01flag_;
	bool alpha02flag_;
	bool drawflag_;
	int drawtime_;
	bool gamestartflag_;
	int alpha01_;
	int alpha02_;
	D3DXQUATERNION qtnAttitude;
	GamePadXbox* GamePad_;
	D3DXVECTOR3 lostresultoffset_;
	D3DXVECTOR3 GameStartOffset_;
	D3DXVECTOR3 resetat_;
	D3DXVECTOR3 reseteye_;
public:
	CCamera(D3DXVECTOR3 _at, D3DXVECTOR3 _eye)
	{
		front_ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		right_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		up_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_Dot_ = 0.0f;
		camerainfo_.at = _at;
		camerainfo_.eye = _eye;
		resetat_ = _at;
		reseteye_ = _eye;
		camerainfo_.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		offset_ = D3DXVECTOR3(0.0f,20.0f,-200.0f);
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
		offset_ = D3DXVECTOR3(0.0f, 20.f, -200.0f);
		resettime_ = 0;
	}
	~CCamera();
public:
	void CameraReset();
	void CameraInit() {}
	void CameraUpdate();
	void CameraDraw() {}
	void CameraUninit() {};

public:
	static D3DXMATRIX GetView();
	static D3DXMATRIX GetProj();
	static D3DXVECTOR3 GetAt();
	static D3DXVECTOR3 GetEye();
	static Entity::YawPitchRoll GetYawPitchRoll();
	static void SetEye(D3DXVECTOR3 _eye);
	static void SetAt(D3DXVECTOR3 _at);
	static void SetView(D3DXMATRIX _view);
	static void SetProj(D3DXMATRIX _proj);
};

