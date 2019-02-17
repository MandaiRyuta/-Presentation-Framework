#pragma once
#include "../../Entity/Entity.h"
#include "../../InputManager/XBoxController.h"

class CCamera
{
private:
	static D3DXMATRIX matrix_view;		// �r���[�ϊ��s��( 4�~4��float�s�� )
	static D3DXMATRIX matrix_projection;		// �v���W�F�N�V�����ϊ��s��( 4�~4��float�s�� )
	D3DXVECTOR3 offset_;	//�I�t�Z�b�g�l
	D3DXVECTOR3 front_;	//�O�x�N�g���l
	D3DXVECTOR3 right_;	//�E�x�N�g���l
	D3DXVECTOR3 up_;	//��x�N�g���l
	bool gamecameraflag_;	//�Q�[���J�n���̉��o���m�F����t���O
	int resettime_;	//�Q�[���ɉf��ׂɕK�v�Ȏ���
	float zoom_;	//��p���g�傷��
	static Entity::CameraInfo camerainfo_;	//�J�������
	static Entity::YawPitchRoll yawpitchroll_;	//���[�s�b�`���[��
	int lastcamerachangetime_;	//�ŏI�I�ȃJ�����̈ړ�����
	int lastzoomtime_;	//�ŏI�I�ȃJ�����̃Y�[������
	int gamestarttime_;	//�Q�[���J�n����
	bool alpha01flag_;	//���l�̐؂�ւ��t���O
	bool alpha02flag_;	//���l�̐؂�ւ��t���O
	bool drawflag_;	//�`��t���O
	int drawtime_;	//�`�掞��
	bool gamestartflag_;	//�Q�[���J�n�t���O
	int alpha01_;	//���l
	int alpha02_;	//���l
	GamePadXbox* GamePad_;	//�Q�[���p�b�h���
	D3DXVECTOR3 resultoffset_;	//���U���g���̃J�����I�t�Z�b�g���W
	D3DXVECTOR3 GameStartOffset_;	//�Q�[���V�[���Ɉړ���������̃I�t�Z�b�g���W
	D3DXVECTOR3 resetat_;	//�����_�̃��Z�b�g
	D3DXVECTOR3 reseteye_;	//�J�����̔z�u�ꏊ���Z�b�g
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
	//@Summary	CameraReset	:	�J�������̃��Z�b�g
	void CameraReset();
	void CameraInit() {}
	void CameraUpdate();
	void CameraDraw() {}
	void CameraUninit() {};

public:
	//@Summary	GetView	:	�r���[�s����擾����֐�
	static D3DXMATRIX GetView();
	//@Summary	GetProj	:	�v���W�F�N�V�����s����擾����֐�
	static D3DXMATRIX GetProj();
	//@Summary	GetAt	:	�����_�����擾����֐�
	static D3DXVECTOR3 GetAt();
	//@Summary	GetEye	:	�J�������W���擾����֐�
	static D3DXVECTOR3 GetEye();
	//@Summary	GetYawPitchRoll	:	���[�s�b�`���[�����擾����֐�
	static Entity::YawPitchRoll GetYawPitchRoll();
	//@Summary	SetEye	:	�J�������W��ݒ肷��֐�
	static void SetEye(D3DXVECTOR3 _eye);
	//@Summary	SetAt	:	�����_��ݒ肷��֐�
	static void SetAt(D3DXVECTOR3 _at);
	//@Summary	SetView	:	�r���[�s���ݒ肷��֐�
	static void SetView(D3DXMATRIX _view);
	//@Summary	SetProj	:	�v���W�F�N�V�����s���ݒ肷��֐�
	static void SetProj(D3DXMATRIX _proj);
};

