#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"
constexpr int MAGIC_NUM = 10;

class MagicObject : public GameObjectManager
{
public:
	MagicObject(int _Priority);
	~MagicObject();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	//@Summary	Create	:	�v���C���[�̖��@�̃I�u�W�F�N�g���쐬����֐�
	static MagicObject* Create(int _Priority);
public:
	//@Summary	StartMagic	:	���@���g�p������
	//@ParamName	=	"target"	:	�ł����ވʒu
	//@ParamName	=	"pos"	:	�v���C���[���r�����Ă���Ƃ��̍��W
	void StartMagic(D3DXVECTOR3 target, D3DXVECTOR3 pos);
private:
	int usetime_;	//�r���������āA�ł܂ł̎���
	int count_;	//�G�t�F�N�g�̕`�掞��
	int objectnum_;	//���@�̃I�u�W�F�N�g��
	bool objectdrawflag_;	//���@�̕`��t���O
	D3DXVECTOR3 TargetVec_[MAGIC_NUM];	//�S�Ă̖��@���^�[�Q�b�g�ɓ��B�����Ƃ��ɉ����֔�Ԃ��w�肷��x�N�g��
	D3DXVECTOR3 OwnerVec_[MAGIC_NUM];	//�S�Ă̖��@�ɊJ�n�ʒu����ǂ̂悤�ɔ�Ԃ��w�肷��x�N�g��
	D3DXVECTOR3 target_;	//�^�[�Q�b�g�̈ʒu
	D3DXVECTOR3 pos_;	//�J�n�ʒu
	Entity::MAGIC_WORK magic[MAGIC_NUM];	//���@�̊J�n�ʒu���G�t�F�N�g���Ɋi�[����
};