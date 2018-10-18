#pragma once
#include "../../Entity/Entity.h"

class CCamera
{
private:
	// ビュー変換行列( 4×4のfloat行列 )
	static D3DXMATRIX matrix_view;
	// プロジェクション変換行列( 4×4のfloat行列 )
	static D3DXMATRIX matrix_projection;

	D3DXVECTOR3 offset;
	
	D3DXVECTOR3 front_;
	D3DXVECTOR3 right_;
	D3DXVECTOR3 up_;

	float m_Dot_;

	static Entity::CameraInfo camerainfo_;
	static Entity::YawPitchRoll yawpitchroll_;
	D3DXMATRIX mtx_right_;
	D3DXMATRIX mtx_up_;
public:
	CCamera(D3DXVECTOR3 _at, D3DXVECTOR3 _eye)
	{
		front_ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		right_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		up_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_Dot_ = 0.0f;
		camerainfo_.at = _at;
		camerainfo_.eye = _eye;
		camerainfo_.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		offset = D3DXVECTOR3(0.0f,20.0f,-200.0f);
	}
	~CCamera();
public:
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

