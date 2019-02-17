#pragma once

class BossMonster;

class BossStatusManager
{
public:
	explicit BossStatusManager() {}
	virtual ~BossStatusManager() {}
	//@Summary	Update	:	�{�X�̃X�e�[�^�X���̍X�V�p�̉��z�֐�
	//@ParamName	=	"_bossmonster"	:	�{�X���
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossStatusNull : public BossStatusManager
{
public:
	BossStatusNull() {}
	virtual ~BossStatusNull() {}
	//@Summary	Update	:	�{�X�̃X�e�[�^�X���̍X�V�����p�̊֐�
	//@ParamName	=	"_bossmonster"	:	�{�X���
	virtual void Update(BossMonster* _bossmonster) override { _bossmonster = _bossmonster; }
};