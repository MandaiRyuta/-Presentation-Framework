#pragma once
#include "../System.h"
/*�{�X�N���X����h����switch�ŃA�j���[�V�����t���[����A�_���[�W�̐ݒ���s���Q�b�g�����違�ǔ��ňړ����x�Ȃ񂩂��ݒ肵�Ă݂�Ƃ悢��������Ȃ�*/
class EnemyBoss : public MySystem
{
public:
	EnemyBoss() {}
	~EnemyBoss() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
};