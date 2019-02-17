#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <unordered_map>
#if _DEBUG
#pragma comment(lib, "Effekseer/src/lib/VS2015/Debug/Effekseer.lib" )
#pragma comment(lib, "Effekseer/src/lib/VS2015/Debug/EffekseerRendererDX9.lib" )
#else
#pragma comment(lib, "Effekseer/src/lib/VS2015/Release/Effekseer.lib" )
#pragma comment(lib, "Effekseer/src/lib/VS2015/Release/EffekseerRendererDX9.lib" )
#endif

#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"

class MyEffekseer : public GameObjectManager
{
public:
	MyEffekseer(int _priority, wchar_t _filepath[]);
	~MyEffekseer();
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

public:
	static MyEffekseer* CreateMyEffect(int _priority, wchar_t _filepath[]);
public:
	//@Summary	SetMovePosition	:	�ړ��ʒu��ݒ肷��
	void SetMovePosition(D3DXVECTOR3 _addmove);
	//@Summary	SetPosition	:	���W���Z�b�g����
	//@ParamName	=	"_targetposition"	:	�ʒu
	void SetPosition(D3DXVECTOR3 _targetposition);
	//@Summary	SetScale	:	�g��l���Z�b�g����
	//@ParamName	=	"_scale"	:	�ݒ肷��g��l
	void SetScale(D3DXVECTOR3 _scale);
	//@Summary	SetRotation	:	��]���Z�b�g����
	//@ParamName	=	"_rotation"	:	��]�̒l
	void SetRotation(D3DXVECTOR3 _rotation);
	//@Summary	SetWorldMatrix	:	���[���h�s����Z�b�g����
	//@ParamName	=	"_location"	:	���[���h�s��ɃZ�b�g����l
	void SetWorldMatrix(Entity::EffectInfomation _location);
	//@Summary	SetIsDrawing	:	�`��ݒ�
	//@ParamName	=	"_drawing"	:	�`��t���O
	void SetIsDrawing(bool _drawing);
private:
	//@Summary	SetEfkWorldMatrix	:	�G�t�F�N�V�A���ɃZ�b�g���郏�[���h�s��
	void SetEfkWorldMatrix(D3DXMATRIX _world);
public:
	//@Summary	PlayEffect	:	�G�t�F�N�g�Đ�
	void PlayEffect();
	//@Summary	StopEffect	:	�G�t�F�N�g��~
	void StopEffect();
public:
	//@Summary	GetPosition	:	�G�t�F�N�g�`�掞�̍��W�����擾����
	const D3DXVECTOR3 GetPosition();
	//@Summary	GetRotation	:	�G�t�F�N�g�`�掞�̉�]�����擾����
	const D3DXVECTOR3 GetRotation();
	//@Summary	GetWorld	:	�G�t�F�N�g�`�掞�̃��[���h�����擾����
	const D3DXMATRIX GetWorld();
	//@Summary	GetFramecount	:	�`�撆�̃t���[���J�E���g���擾����
	const float GetFrameCount();
public:
	//@Summary	SetFramecount	:	�t���[���J�E���g��ݒ肷��
	//@_deltatime	:	1�t���[�����̑����l��ݒ�
	void SetFrameCount(float _deltatime);
private:
	float deltaframe_;	//1�t���[���ŃJ�E���g�����l
	bool IsDrawing_;	//�`��t���O
	bool PlayFlag_;		//�Đ��t���O
	D3DXMATRIX world_;	//���[���h�s��
	Effekseer::Manager* MyEfkManager_;	//�G�t�F�N�V�A�}�l�[�W���[
	EffekseerRendererDX9::Renderer* MyEfkRenderer_;	//�G�t�F�N�V�A�����_���[
	Effekseer::Effect*	MyEfkEffect_;	//�G�t�F�N�V�A���̃p�����[�^�[
	Effekseer::Handle	MyEfkHandle_;	//�G�t�F�N�V�A���̃n���h�����
	Entity::EffectInfomation location_;	//�G�t�F�N�g�`��ɕK�v�ȏ��
};