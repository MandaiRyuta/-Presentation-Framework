#pragma once
#include "../../Entity/Entity.h"
#include "../../InputManager/XBoxController.h"

class CCamera
{
private:
	static D3DXMATRIX matrix_view;		// ビュー変換行列( 4×4のfloat行列 )
	static D3DXMATRIX matrix_projection;		// プロジェクション変換行列( 4×4のfloat行列 )
	D3DXVECTOR3 offset_;	//オフセット値
	D3DXVECTOR3 front_;	//前ベクトル値
	D3DXVECTOR3 right_;	//右ベクトル値
	D3DXVECTOR3 up_;	//上ベクトル値
	bool gamecameraflag_;	//ゲーム開始時の演出を確認するフラグ
	int resettime_;	//ゲームに映る為に必要な時間
	float zoom_;	//画角を拡大する
	static Entity::CameraInfo camerainfo_;	//カメラ情報
	static Entity::YawPitchRoll yawpitchroll_;	//ヨーピッチロール
	int lastcamerachangetime_;	//最終的なカメラの移動時間
	int lastzoomtime_;	//最終的なカメラのズーム時間
	int gamestarttime_;	//ゲーム開始時間
	bool alpha01flag_;	//α値の切り替えフラグ
	bool alpha02flag_;	//α値の切り替えフラグ
	bool drawflag_;	//描画フラグ
	int drawtime_;	//描画時間
	bool gamestartflag_;	//ゲーム開始フラグ
	int alpha01_;	//α値
	int alpha02_;	//α値
	GamePadXbox* GamePad_;	//ゲームパッド情報
	D3DXVECTOR3 resultoffset_;	//リザルト時のカメラオフセット座標
	D3DXVECTOR3 GameStartOffset_;	//ゲームシーンに移動した直後のオフセット座標
	D3DXVECTOR3 resetat_;	//注視点のリセット
	D3DXVECTOR3 reseteye_;	//カメラの配置場所リセット
public:
	CCamera(D3DXVECTOR3 _at, D3DXVECTOR3 _eye)
	{
		front_ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		right_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		up_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		camerainfo_.at = _at;
		camerainfo_.eye = _eye;
		resetat_ = _at;
		reseteye_ = _eye;
		camerainfo_.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		offset_ = D3DXVECTOR3(0.0f,20.0f,-200.0f);
		zoom_ = D3DX_PI / 3;
		lastcamerachangetime_ = 0;
		lastzoomtime_ = 0;
		yawpitchroll_.pitch = 0.0f;
		yawpitchroll_.roll = 0.0f;
		yawpitchroll_.yaw = 0.0f;
		resultoffset_ = D3DXVECTOR3(offset_.x, offset_.y, offset_.z + 120.0f);
		GameStartOffset_ = offset_;
		gamestarttime_ = 0;
		gamecameraflag_ = false;
		offset_ = D3DXVECTOR3(0.0f, 20.f, -200.0f);
		resettime_ = 0;
	}
	~CCamera();
public:
	//@Summary	CameraReset	:	カメラ情報のリセット
	void CameraReset();
	void CameraInit() {}
	void CameraUpdate();
	void CameraDraw() {}
	void CameraUninit() {};

public:
	//@Summary	GetView	:	ビュー行列を取得する関数
	static D3DXMATRIX GetView();
	//@Summary	GetProj	:	プロジェクション行列を取得する関数
	static D3DXMATRIX GetProj();
	//@Summary	GetAt	:	注視点情報を取得する関数
	static D3DXVECTOR3 GetAt();
	//@Summary	GetEye	:	カメラ座標を取得する関数
	static D3DXVECTOR3 GetEye();
	//@Summary	GetYawPitchRoll	:	ヨーピッチロールを取得する関数
	static Entity::YawPitchRoll GetYawPitchRoll();
	//@Summary	SetEye	:	カメラ座標を設定する関数
	static void SetEye(D3DXVECTOR3 _eye);
	//@Summary	SetAt	:	注視点を設定する関数
	static void SetAt(D3DXVECTOR3 _at);
	//@Summary	SetView	:	ビュー行列を設定する関数
	static void SetView(D3DXMATRIX _view);
	//@Summary	SetProj	:	プロジェクション行列を設定する関数
	static void SetProj(D3DXMATRIX _proj);
};

