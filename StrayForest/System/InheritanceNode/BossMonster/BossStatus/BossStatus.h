#pragma once
#include "BossStatusManager.h"
#include "../../../Entity/Entity.h"
#include "../../../../GameObjectManager/GameObjectManager.h"
#include "../../../Polygon3D.h"
#include "../../../Polygon2D.h"
#include "../../../colision/SphereColision.h"

class BossStatus : public BossStatusManager
{
public:
	explicit BossStatus();
	virtual ~BossStatus();
	//@Summary	Update	:	�{�X�̃X�e�[�^�X���̍X�V����
	//@ParamName	=	"_bossmonster"	:	�{�X���
	virtual void Update(BossMonster* _bossmonster);
private:
	bool damegeactionflag_;	//�_���[�W���󂯂��Ƃ��A�j���[�V�������s���悤�ɂ����邽�߂̃t���O
	int damegeactiioncount_;	//�_���[�W���󂯂�񐔂��J�E���g����
	bool damegeflag_;	//�_���[�W��^����ۂɎg���t���O
	int damegeframe_;	//�_���[�W�󂯂��Ƃ��̃��[�V�����p�t���[���J�E���g
	float PlayerHitScale_;	//�v���C���[����p�̋��̔��a
	float EnemyHitScale_;	//�{�X�̔���p�̋��̔��a
	int damegecount_;	//�����U�肩���������Ƀ����t���[�������_���[�W��^����悤�ɂ��邽��
	D3DXVECTOR3 bosshitpos_;	//�{�X���_���[�W���������ʒu
	D3DXVECTOR3 weponcolisionset_;	//�v���C���[�̌��̏Փ˔�����W
	SphereColision attackcolision_;	//�v���C���[�̍U�����ɏՓ˔�����������
	Entity::SphereColision attackcheck_;	//�����	�{�X�̓��̂ƃv���C���[�̌�
	int frame_;	//�_���[�W�G�t�F�N�g�p�̃t���[���J�E���g
	bool effectdrawflag_;	//�G�t�F�N�g�̕`��t���O
};