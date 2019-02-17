#pragma once

class BossMonster;
class BossMonsterAttackPattern
{
public:
	virtual ~BossMonsterAttackPattern() {}
	//@Summary	Update	:	�{�X�̒ʏ�U���̍X�V�p�̉��z�֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	virtual void Update(BossMonster* _bossmonster) = 0;
};

class BossMonsterAttackNone : public BossMonsterAttackPattern
{
	//@Summary	Update	:	�{�X�̒ʏ�U���̍X�V�p�̊֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	void Update(BossMonster* _bossmonster) override {}
};