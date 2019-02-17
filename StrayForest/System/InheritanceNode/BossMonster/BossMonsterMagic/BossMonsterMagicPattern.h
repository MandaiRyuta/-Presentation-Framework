#pragma once

class BossMonster;
class BossMonsterMagicPattern
{
public:
	virtual ~BossMonsterMagicPattern() {}
	//@Summary	Update	:	�{�X�̖��@�U���̍X�V�p�̉��z�֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossMonsterMagicNone : public BossMonsterMagicPattern
{
public:
	~BossMonsterMagicNone() {}
	//@Summary	Update	:	�{�X�̖��@�U���̍X�V�p�̊֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	void Update(BossMonster* _bossmonster) override {}
};