#pragma once
#include "BossMonsterMagicPattern.h"
#include "../../../Entity/Entity.h"
#include "../../../colision/SphereColision.h"

class BossMonsterMagicPatternB : public BossMonsterMagicPattern
{
public:
	BossMonsterMagicPatternB();
	~BossMonsterMagicPatternB();
	//@Summary	Update	:	�{�X�̖��@�U���̍X�V�p�̊֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//�t���[���J�E���g
	bool MagicEffectDrawFlag_;	//���@�g�p�t���O
	D3DXVECTOR3 Position_;	//���@�`��p�̍��W
	bool Damegecheck_;	//���@���������Ă���_���[�W��^����悤�ɂ��邽�߂̃t���O
	bool ColisionCheck_;	//�Փˊm�F�t���O
	bool GetDamegeFlag_;	//�r�����I�������Ƃ��Ƀ_���[�W��^����悤�ɂ��邽�߂̃t���O
	SphereColision colision_;	//�Փ˔���p�̕ϐ�
	Entity::SphereColision spherecolision_;	//�����
};